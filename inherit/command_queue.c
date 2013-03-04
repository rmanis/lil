
#include <globals.h>

inherit __DIR__ "command_queue/alias";

void execute(string command);
void try_execute(string command);
void clear_queue();
string *get_command_queue();
varargs string *remove_first_slice(int num);

int get_speed();
void set_speed(int speed);

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

int get_speed() {
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

void execute(string arg) {
    string *parts = explode(arg, " ");
    string verb = sizeof(parts) ? parts[0] : "";
    string rest = implode(parts[1..], " ");
    string cmd_path = COMMAND_PREFIX + verb;
    object cobj = load_object(cmd_path);
    object destination;
    string direction = unabbreviate_direction(verb);

    if (is_direction(direction) && !strlen(trim(rest))) {
        destination = here()->destination(direction);
        if (destination) {
            MOVE_D->move_direction(this_object(), direction);
        } else {
            MESSAGE_D->tell(this_object(),
                    "There doesn't seem to be an exit in that direction.\n");
        }
    } else if (cobj) {
        cobj->main(rest);
    } else {
        if (!destination && strlen(arg)) {
            MESSAGE_D->tell(this_object(), "What?\n");
        }
    // maybe call an emote/soul daemon here
    }
}

void try_execute(string command) {
    string *parts = explode(trim(command), " ");
    string verb = sizeof(parts) ? parts[0] : "";
    string rest = implode(parts[1..], " ");
    string alias = get_alias(verb);
    string *cmds;
    string cmd;

    if (alias) {
        alias = alias + " " + rest;
        cmds = explode(alias, ";");
        foreach (cmd in cmds) {
            try_execute(cmd);
        }
    } else if (execution_count < get_speed()) {
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

string *get_command_queue() {
    if (!command_queue) {
        command_queue = ({ });
    }
    return command_queue;
}

varargs string *remove_first_slice(int num) {
    // int command_count = sizeof(command_queue);
    int take = (num > 0 ? num : get_speed()) - 1;
    string *slice = get_command_queue()[0..take];
    command_queue = command_queue[take+1..];

    return slice;
}
