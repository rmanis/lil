
#include <globals.h>

int main(string arg) {
    string *files = explode(arg, " ");
    string file;

    foreach (file in files) {
        file = resolve_path(this_player()->query_cwd(), file);
        if(!sizeof(stat(file))) {
            ensure_path_of_file_exists(file);
            write_file(file, "");
        }
    }

    return 1;
}
