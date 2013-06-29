
#include <globals.h>

inherit __DIR__ "command_queue/alias";

string which_command(string verb);
void execute(string command);
void try_execute(string command);
void clear_queue();
string *query_command_queue();

string *query_command_paths();
void set_command_paths(string *paths);
string *add_command_path(string path);
void ensure_wizard_paths();
void ensure_no_wizard_paths();

varargs string *remove_first_slice(int num);

int query_speed();
void set_speed(int speed);

string *command_paths;
string *command_queue;
int execution_count;
int speed;

void heart_beat() {
    string *commands = remove_first_slice();
    string command;

    execution_count = 0;

    foreach (command in commands) {
        execute(command);
        execution_count++;
    }
}

int query_speed() {
    if (!speed) {
        speed = DEFAULT_SPEED;
    }
    return speed;
}

void set_speed(int new_speed) {
    if (speed > 0) {
        speed = new_speed;
    }
}

string which_command(string verb) {
    string *possibilities;
    string *existing;

    if (strlen(verb)) {
        possibilities = map(query_command_paths(),
                (: $1 + "/" + $2 + ".c" :), verb);
        existing = filter(possibilities, (: filep($1) :));

        if (sizeof(existing)) {
            return existing[0];
        }
    }

    return "";
}

mixed *deep_parser_inv(object thing) {
    mixed *thing_inv;
    mixed item;
    mixed item_inv;
    mixed *r = 0;

    thing_inv = all_inventory(thing);
    if (sizeof(thing_inv)) {
        r = ({ });

        foreach (item in thing_inv) {
            item_inv = deep_parser_inv(item);

            if (item_inv) {
                r += ({ item, item_inv });
            } else {
                r += ({ item });
            }
        }
    }

    return r;
}

void execute(string arg) {
    string *parts = explode(arg, " ");
    string verb = sizeof(parts) ? parts[0] : "";
    string rest = implode(parts[1..], " ");
    string cmd_path = which_command(verb);
    object cobj = load_object(cmd_path);
    mixed destination;
    string direction = unabbreviate_direction(verb);
    mixed accessible;
    mixed par;

    mixed h = here();
    accessible = ({ h, deep_parser_inv(h) });
    // DEB(accessible);
    par = parse_sentence(arg, 0, accessible);

    if (stringp(par)) {
        MESSAGE_D->tell(this_object(), par);
    } else if (!par) {

        if (here() && is_direction(direction) && !strlen(trim(rest))) {
            destination = here()->destination(direction);
            if (destination) {
                MOVE_D->move_direction(this_object(), direction);
            } else {
                MESSAGE_D->tell(this_object(),
                        "There doesn't seem to be an exit in that direction.\n");
            }
        } else if (!here() && is_direction(direction)) {
            MESSAGE_D->tell(this_object(),
                    "You can't move if you're not anywhere.\n");
        } else if (cobj) {
            cobj->main(rest);
        } else {
            if (!destination && strlen(arg)) {
                MESSAGE_D->tell(this_object(), "What?\n");
            }
        // maybe call an emote/soul daemon here
        }
    }
}

void try_execute(string command) {
    string *parts = explode(trim(command), " ");
    string verb = sizeof(parts) ? parts[0] : "";
    string rest = implode(parts[1..], " ");
    string alias = query_alias(verb);
    string *cmds;
    string cmd;

    if (alias) {
        alias = alias + (strlen(rest) ? " " + rest : "");
        cmds = explode(alias, ";");
        foreach (cmd in cmds) {
            try_execute(cmd);
        }
    } else if (execution_count < query_speed()) {
        execute(command);
        execution_count++;
    } else {
        command_queue += ({ command });
        MESSAGE_D->tell(this_object(),
                sprintf("Queued command '%s'\n", command));
    }
}

void clear_queue() {
    command_queue = ({ });
    execution_count = 6;
    MESSAGE_D->tell(this_object(), "Command queue cleared\n");
}

string *query_command_queue() {
    if (!command_queue) {
        command_queue = ({ });
    }
    return command_queue;
}

string *query_command_paths() {
    if (!command_paths) {
        command_paths = ({ USER_PATH });
    }
    return command_paths;
}

void set_command_paths(string *paths) {
    command_paths = paths;
}

string *add_command_path(string path) {
    set_command_paths(({ path }) + query_command_paths());
    return command_paths;
}

void ensure_wizard_paths() {
    if (member_array(WIZ_PATH, query_command_paths()) < 0) {
        add_command_path(WIZ_PATH);
    }
}

void ensure_no_wizard_paths() {
    set_command_paths(query_command_paths() - ({ WIZ_PATH }));
}

varargs string *remove_first_slice(int num) {
    // int command_count = sizeof(command_queue);
    int take = (num > 0 ? num : query_speed()) - 1;
    string *slice = query_command_queue()[0..take];
    command_queue = command_queue[take+1..];

    return slice;
}
