
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string *filenames = explode(arg, " ");
    string file;
    string path;
    int count = sizeof(filenames);

    if (!count) {
        return error_out("Usage: cat { <file> }");
    }

    foreach (file in filenames) {
        path = resolve_path(this_player()->query_cwd(), file);

        if (sizeof(stat(path))) {
            cat(path);
        }
    }

    return 1;
}
