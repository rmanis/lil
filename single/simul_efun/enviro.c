
#include <globals.h>

object here();

string opposite(string direction);
string unabbreviate_direction(string direction);
string abbreviate_direction(string direction);
int is_direction(string direction);

object here() {
    return environment(this_player());
}

string *cardinal_directions = ({
        "north",
        "south",
        "east",
        "west",
        "northeast",
        "southwest",
        "northwest",
        "southeast"
        });

mapping opposites = ([
        "north" : "south",
        "south" : "north",
        "east" : "west",
        "west" : "east",
        "northeast" : "southwest",
        "southwest" : "northeast",
        "northwest" : "southeast",
        "southeast" : "northwest",
        "in" : "out",
        "out" : "in",
        "up" : "down",
        "down" : "up",
        ]);
string opposite(string direction) {
    return opposites[direction];
}

mapping direction_abbreviations = ([
        "n" : "north",
        "s" : "south",
        "e" : "east",
        "w" : "west",
        "ne" : "northeast",
        "sw" : "southwest",
        "nw" : "northwest",
        "se" : "southeast",
        "u" : "up",
        "d" : "down"
        ]);
string unabbreviate_direction(string direction) {
    string unabbreviate = direction_abbreviations[direction];
    return unabbreviate ? unabbreviate : direction;
}

mapping reverse_direction_abbreviations = ([
        "north" : "n",
        "south" : "s",
        "east" : "e",
        "west" : "w",
        "northeast" : "ne",
        "southwest" : "sw",
        "northwest" : "nw",
        "southeast" : "se",
        "up" : "u",
        "down" : "d"
        ]);
string abbreviate_direction(string direction) {
    string abbrev = reverse_direction_abbreviations[direction];
    return abbrev ? abbrev : direction;
}

int is_direction(string direction) {
    return opposites[direction] || (here() && here()->has_direction(direction));
}

string as_place(string direction) {
    if (member_array(direction, cardinal_directions) >= 0) {
        return "the " + direction;
    }
    switch (direction) {
        case "in": return "inside";
        case "out" : return "outside";
        case "up": return "above";
        case "down": return "below";
    }
    return direction;
}
