
#include <globals.h>

mixed direct_drop_obj(object obj, string ob_text);

mixed direct_drop_obj(object obj, string ob_text) {
    if (environment(obj) != this_user()) {
        return "You don't have " + obj->query_in_room_name() + "\n";
    }
    return 1;
}
