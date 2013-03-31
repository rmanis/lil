
#include <globals.h>

int main(string arg) {

    string base = trim(arg) + ".c";
    string path = resolve_path(this_player()->query_cwd(), base);
    object ob;

    if (!filep(path)) {
        previous_object()->tell("No such object: " + path + "\n");
        return 0;
    }

    ob = new(path);

    ob->move(environment(previous_object()));

    return 1;
}
