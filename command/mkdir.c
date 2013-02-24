
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string *filenames = explode(arg, " ");
    string path;
    int count = sizeof(filenames);

    filenames = map(filter(filenames, (: strlen($1) :)),
            (: resolve_path(this_player()->query_cwd(), $1) :));

    foreach (path in filenames) {
        if (!mkdir(path)) {
            output("%s already exists.\n", path);
        }
    }

    return 1;
}
