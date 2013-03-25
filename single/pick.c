
#include <globals.h>

// The pick daemon.  Picks what object is meant by a name.

int is_num(string str);
mixed *parse_names(string str);
object *parse_names_for_player(object player, string str);
varargs mixed pick_for_player(object player, string thing, int specifier);
object find_in_array_by_name(string name, object *arr);
object *find_all_in_arr_by_name(string name, object *arr);

int is_num(string str) {
    return regexp(str, "^[0-9]+$");
}

string *parse_list(string str) {
    mapping *parse = parse_names(str);
    mapping m;
    string current;
    string *arr = allocate(sizeof(parse));
    int i = 0;

    foreach (m in parse) {
        if (!m["thing"] || (m["specifier"] && m["count"])) {
            continue;
        }

        // TODO: handle cases like "2 swords"
        if (m["specifier"]) {
            current = sprintf("%s %d", m["thing"], m["specifier"]);
        } else {
            current = m["thing"];
        }

        arr[i++] = current;
    }

    return arr;
}

mixed *parse_names(string str) {
    mixed *arr;
    int count;
    int i;
    mapping *things;
    int num_things = 1;
    int thing_index = 0;
    mixed current;

    if (!str || !strlen(trim(str))) {
        return 0;
    }

    arr = reg_assoc(trim(str), ({ "[, ]" }), ({ 1 }))[0];
    count = sizeof(arr);

    for (i = 0; i < count; i++) {
        if (arr[i] == "and" || arr[i] == ",") {
            num_things++;
            arr[i] = ",";
        }
    }

    arr = filter(arr, (: $1 && strlen(trim($1)) :));
    count = sizeof(arr);

    things = allocate(num_things);

    current = 0;
    for (i = 0; i < count; i++) {
        if (arr[i] == ",") {
            things[thing_index++] = current;
            current = 0;
        } else if (is_num(arr[i])) {
            if (!current) {
                current = allocate_mapping(3);
            }
            if (current["thing"]) {
                sscanf(arr[i], "%d", current["specifier"]);
            } else {
                // TODO: spelt out numbers
                sscanf(arr[i], "%d", current["count"]);
            }
        } else {
            if (!current) {
                current = allocate_mapping(3);
            }
            current["thing"] = arr[i];
        }
    }
    if (current) {
        things[thing_index++] = current;
    }

    return things;
}

object *parse_names_for_player(object player, string str) {
    mapping *things = parse_names(str);
    return map(things,
            (: pick_for_player($2, $1["thing"], $1["specifier"]) :),
            player);
}

varargs mixed pick_for_player(object player, string thing, int specifier) {
    object *inv;
    object *env;
    object *errthang;
    object *things;
    object room;
    mixed target;

    specifier = specifier ? specifier : 1;

    if (thing == "me" || thing == "myself") {
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

    if (!target) {
        target = thing;
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
