
#include <globals.h>

inherit __DIR__ "command_queue/alias";

void execute(string command);
void try_execute(string command);
string *get_command_queue();
varargs string *remove_first_slice(int num);

string *command_queue;
int execution_count;

void heart_beat() {
    string *commands = remove_first_slice();
    string command;

    execution_count = 0;

    foreach (command in commands) {
        execute(command);
        execution_count++;
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
    string alias = get_alias(verb);

    if (alias) {
        execute(alias + " " + rest);
    } else if (is_direction(direction) && !strlen(trim(rest))) {
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
    if (execution_count < 6) {
        execute(command);
        execution_count++;
    } else {
        command_queue += ({ command });
        MESSAGE_D->tell(this_object(),
                sprintf("Queued command '%s'\n", command));
    }
}

string *get_command_queue() {
    if (!command_queue) {
        command_queue = ({ });
    }
    return command_queue;
}

varargs string *remove_first_slice(int num) {
    // int command_count = sizeof(command_queue);
    int take = (num > 0 ? num : 6) - 1;
    string *slice = get_command_queue()[0..take];
    command_queue = command_queue[take+1..];

    return slice;
}
