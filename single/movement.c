
#include <globals.h>

// The movement daemon.

#define G(msg) color_surround("green", msg)

int move(mixed thing, mixed destination);
int move_direction(object thing, string direction);
varargs void tell_players(object *players, string str);
void report_move(object thing, object from, object to,
        string leave_msg1, string leave_msg3, string arrive_msg);

varargs int move(mixed thing, mixed destination, int teleport) {
    object dest_obj;
    object from = environment(thing);
    string direction_to, direction_from;
    string leave;
    string arrive;

    if (stringp(destination)) {
        dest_obj = load_object(destination);
    } else if (objectp(destination)) {
        dest_obj = destination;
    }

    if (!dest_obj) {
        return 0;
    }

    if (teleport) {
        leave = "$N $vturn to dust which blows away.";
        arrive = "$N $vappear from somewhere.";
    } else {
        direction_to = from->direction_to(dest_obj);
        direction_from = dest_obj->direction_to(from);

        leave = sprintf("$N $vleave %s.", direction_to);
        arrive = sprintf("$N $varrive from %s.", direction_from);
    }

    thing->move(dest_obj, G(leave), G(arrive));

    return 1;
}

int move_direction(object thing, string direction) {
    object from = environment(thing);
    object destination;
    string dest_str;

    string leave_msg1;
    string leave;
    string arrive;

    mapping attribs = from->attributes(direction);
    string exit_leave = attribs[LEAVE];
    string exit_arrive = attribs[ARRIVE];

    if (!from) {
        return 0;
    }

    dest_str = from->destination(direction);
    if (strlen(dest_str)) {
        destination = load_object(dest_str);
    }

    if (destination) {
        leave = exit_leave || sprintf("$N $vleave %s.", direction);
        arrive = exit_arrive ||
            sprintf("$N $varrive from %s.", destination->direction_to(from));
        thing->move(destination, G(leave), G(arrive));
    } else {
        leave_msg1 = sprintf("You attempt to go %s, "
                "but something stops you....", direction);
        leave = sprintf("$N $vstart going %s, but $vappear to have great "
                "difficulty moving.", direction);
        MESSAGE_D->my_action(thing, G(leave_msg1));
        MESSAGE_D->other_action(thing, G(leave));
    }

    return 1;
}
