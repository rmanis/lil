
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string *words = explode(arg, " ");
    string command;
    string command_path;
    object ob;

    if (!sizeof(words)) {
        return error_out("Usage: dev <command> {<args>}");
    }

    command = words[0];
    command_path = previous_object()->which_command(command);

    ob = find_object(command_path);
    if (ob) {
        destruct(ob);
    }

    this_player()->process_input(arg);
    return 1;
}
