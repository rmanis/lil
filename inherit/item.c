
#include <globals.h>

inherit BASE;

// The base item object

mixed direct_get_obj(object obj, string ob_text);
mixed direct_drop_obj(object obj, string ob_text);

mixed direct_get_obj(object obj, string ob_text) {
    if (environment(obj) != environment(this_user())) {
        return "You can't get that.\n";
    }
    return 1;
}

mixed direct_drop_obj(object obj, string ob_text) {
    if (environment(obj) != this_user()) {
        return "You don't have " + obj->query_in_room_name() + "\n";
    }
    return 1;
}
