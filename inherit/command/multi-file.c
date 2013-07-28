
#include <globals.h>

inherit "/inherit/error_out";

string usage();
void operate(string path);
int condition(string path);
void pre_op(string *paths);
int post_op();

int main(string arg) {
    string *filenames = explode(arg, " ");
    string *paths;
    string path;
    int count = sizeof(filenames);

    if (!count) {
        return error_out(usage());
    }

    paths = map(filenames, (: resolve_path(this_player()->query_cwd(), $1) :));
    pre_op(paths);

    foreach (path in paths) {
        if (condition(path)) {
            operate(path);
        }
    }

    return post_op();
}

int condition(string path) {
    return sizeof(stat(path));
}

void pre_op(string *paths) {
}

int post_op() {
    return 1;
}
