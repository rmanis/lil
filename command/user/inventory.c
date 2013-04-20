
#include <globals.h>

inherit "/inherit/error_out";
inherit "/inherit/itemize";

int main(string arg) {
    object *objs;
    string prefix = "You are carrying: ";
    string str;

    if (strlen(trim(arg))) {
        return error_out("usage: inventory");
    }

    objs = all_inventory(previous_object());
    str = itemize(objs->query_in_room_name());

    if (sizeof(objs)) {
        previous_object()->tell(prefix + str + "\n", strlen(prefix));
    } else {
        previous_object()->tell("You are not carrying anything.\n");
    }

    return 1;
}
