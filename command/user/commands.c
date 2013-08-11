
#include <globals.h>

inherit "/inherit/tablefy";

string *cleanse(string *commands);
mixed *detail(string command);

int main(string arg) {
    string *paths = this_player()->query_command_paths();
    string *commands;
    mixed *detailed;
    string path;

    foreach (path in paths) {
        commands = cleanse(get_dir(path + "/"));
        detailed = map(commands, (: detail :));
        printf("%s commands:\n", basename(path));
        print_table(tablefy(detailed));
        printf("\n");
    }

    return 1;
}

string *cleanse(string *commands) {
    string *files;
    string *r;

    files = filter(commands, (: $1[0] != '.' :));
    r = map(files, (: basename($1, ".c") :));

    return r;
}

mixed *detail(string command) {
    return ({ command, strlen(command) });
}
