
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string *filenames = explode(arg, " ");
    string path;
    object obj;
    int exists;
    int count = sizeof(filenames);

    if (!count) {
        return error_out("Usage: update { <file> }");
    }

    filenames = map(filter(filenames, (: strlen($1) :)),
            (: resolve_path(this_player()->query_cwd(), $1) :));

    foreach (path in filenames) {
        if (!(sizeof(stat(path + ".c")) || sizeof(stat(path)))) {
            exists = 0;
            output(path + " does not exist.\n");
        } else {
            exists = 1;
        }

        if (obj = find_object(path)) {
            destruct(obj);
        }

        if (!load_object(path) && exists) {
            output("Could not update " + path + "\n");
        }
    }
    return 1;
}
