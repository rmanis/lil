
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string *filenames = explode(arg, " ");
    string path;
    int count = sizeof(filenames);

    if (!count) {
        return error_out("Usage: rm { <file> }");
    }

    filenames = map(filter(filenames, (: strlen($1) :)),
            (: resolve_path(this_player()->query_cwd(), $1) :));

    foreach (path in filenames) {
        if (!rm(path)) {
            output("Could not remove %s.\n", path);
        }
    }

    return 1;
}
