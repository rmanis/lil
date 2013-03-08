
// The movement daemon.

int move(mixed thing, mixed destination);
int move_direction(object thing, string direction);
varargs void tell_players(object *players, string str);
void report_move(object thing, object from, object to,
        string leave_msg1, string leave_msg3, string arrive_msg);
void tell(int indent, object player, string str);

varargs int move(mixed thing, mixed destination, int teleport) {
    object dest_obj;
    object from = environment(thing);
    string direction_to, direction_from;
    string leave1;
    string leave3;
    string arrive3;

    if (stringp(destination)) {
        dest_obj = load_object(destination);
    } else if (objectp(destination)) {
        dest_obj = destination;
    }

    if (!dest_obj) {
        return 0;
    }

    if (teleport) {
        leave1 = "You are transported somewhere.\n";
        leave3 = sprintf("%s turns to dust which blows away.\n",
                thing->query_name());
        arrive3 = sprintf("%s arrives from somewhere.\n", thing->query_name());
    } else {
        direction_to = from->direction_to(dest_obj);
        direction_from = dest_obj->direction_to(from);

        leave1 = sprintf("You move %s.\n", direction_to);
        leave3 = sprintf("%s leaves %s.\n", thing->query_name(), direction_to);
        arrive3 = sprintf("%s arrives from %s.\n", thing->query_name(),
                direction_from);
    }

    report_move(thing, environment(thing), dest_obj, leave1, leave3, arrive3);
    thing->move(dest_obj);

    return 1;
}

int move_direction(object thing, string direction) {
    object from = environment(thing);
    object destination;
    string dest_str;

    string leave_msg1;
    string leave_msg3;
    string arrival_msg;

    if (!from) {
        return 0;
    }

    dest_str = from->destination(direction);
    if (strlen(dest_str)) {
        destination = load_object(dest_str);
    }

    if (destination) {
        leave_msg1 = sprintf("You walk %s.\n", direction);
        leave_msg3 = sprintf("%s leaves %s.\n", thing->query_name(),
                direction);
        arrival_msg = sprintf("%s arrives from %s.\n", thing->query_name(),
                destination->direction_to(from));

    } else {
        leave_msg1 = sprintf("You attempt to go %s, "
                "but something stops you....\n", direction);
        leave_msg3 = sprintf("%s starts going %s, but appears to have great "
                "difficulty moving.\n", thing->query_name(), direction);
    }

    report_move(thing, from, destination, leave_msg1, leave_msg3, arrival_msg);
    if (destination) {
        thing->move(destination);
    }
    return 1;
}

void report_move(object thing, object from, object to,
        string leave_msg1, string leave_msg3, string arrive_msg) {
    object *leave_witnesses;
    object *arrival_witnesses;
    object *exclude = ({ thing });

    if (from) {
        leave_witnesses = filter(all_inventory(from), (: interactive($1) :));
    }
    if (to) {
        arrival_witnesses = filter(all_inventory(to), (: interactive($1) :));
    }

    tell(0, thing, leave_msg1);
    tell_players(leave_witnesses, leave_msg3, exclude);
    tell_players(arrival_witnesses, arrive_msg, exclude);
}

varargs void tell_players(object *players, string str, object *exclude) {
    object p;
    if (strlen(str) && sizeof(players)) {
        foreach (p in players) {
            if (member_array(p, exclude) < 0) {
                p->tell(color_surround("green", str), 0);
            }
        }
    }
}

void tell(int indent, object player, string str) {
    player->tell(color_surround("green", str), indent);
}

