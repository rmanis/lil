
#include <globals.h>

inherit "/inherit/error_out";

string usage();
void operate(string path);
int condition(string path);

int main(string arg) {
    string *filenames = explode(arg, " ");
    string file;
    string path;
    int count = sizeof(filenames);

    if (!count) {
        return error_out(usage());
    }

    foreach (file in filenames) {
        path = resolve_path(this_player()->query_cwd(), file);

        if (condition(path)) {
            operate(path);
        }
    }

    return 1;
}

int condition(string path) {
    return sizeof(stat(path));
}
