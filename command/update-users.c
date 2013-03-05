
#include <globals.h>

int main(string arg) {
    object *players = users();
    string *files = deep_inherit_list(players[0]) + ({ USER_OB });
    string file;
    object o;

    foreach (file in files) {
        o = find_object(file);
        if (o) {
            destruct(o);
        }
    }

    foreach (o in players) {
        o->swap_out();
    }

    return 1;
}
