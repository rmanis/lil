
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string direction = unabbreviate_direction(trim(arg));
    object room = here();
    mapping exits = room->query_exits();
    mapping attributes;

    attributes = exits[direction];
    if (!attributes) {
        return error_out("There is no exit in that direction.");
    }

    if (!attributes[SUBTLE]) {
        return error_out("That exit is already obvious.");
    }

    attributes[SUBTLE] = 0;
    previous_object()->tell(sprintf("Made exit %s obvious.\n", direction));

    return 1;
}
