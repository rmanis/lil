
#include <globals.h>

// The pick daemon.  Picks what object is meant by a name.

varargs object pick_for_player(object player, string thing, int specifier);
object find_in_array_by_name(string name, object *arr);
object *find_all_in_arr_by_name(string name, object *arr);

varargs object pick_for_player(object player, string thing, int specifier) {
    object *inv;
    object *env;
    object *errthang;
    object *things;
    object room;
    object target;

    specifier = specifier ? specifier : 1;

    if (thing == "me" || string == "myself") {
        return player;
    }

    if (player && thing && strlen(thing)) {
        room = environment(player);

        if (room) {
            inv = all_inventory(player);
            env = all_inventory(room);
            errthang = inv + env;

            things = find_all_in_arr_by_name(thing, errthang);
            if (specifier > 0 && specifier <= sizeof(things)) {
                target = things[specifier - 1];
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

object *find_all_in_arr_by_name(string name, object *arr) {
    return filter(arr, (: $1->query_name() == $2 :), name);
}
