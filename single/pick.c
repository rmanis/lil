
#include <globals.h>

// The pick daemon.  Picks what object is meant by a name.

object pick_for_player(object player, string thing);
object find_in_array_by_name(string name, object *arr);

object pick_for_player(object player, string thing) {
    object *inv;
    object *env;
    object room;
    object target;

    if (player && thing && strlen(thing)) {
        room = environment(player);

        if (room) {
            inv = all_inventory(player);

            target = find_in_array_by_name(thing, inv);

            if (!target) {
                env = all_inventory(room);
                target = find_in_array_by_name(thing, env);
            }
        }
    }

    return target;
}

object find_in_array_by_name(string name, object *arr) {
    int index = member_array(name, map(arr, (: $1->query_name() :)));
    if (index >= 0) {
        return arr[index];
    }
}
