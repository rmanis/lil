
#include <globals.h>

inherit "/inherit/error_out";

int is_dir(string path);

int main(string arg) {
    string *filenames = explode(arg, " ");

    if (sizeof(filenames) != 2) {
        return error_out("Usage: cp <source> <destination>");
    }

    filenames = map(filenames, (: resolve_path(this_player()->query_cwd(), $1) :));
    cp(filenames[0], filenames[1]);
}
