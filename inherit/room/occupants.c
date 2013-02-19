
inherit "/inherit/itemize";

object *get_players();
object *get_items();
void write_occupants();

object *get_players() {
    return filter(all_inventory(this_object()), (: interactive($1) :));
}

object *get_items() {
    return filter(all_inventory(this_object()), (: !interactive($1) :));
}

void write_occupants() {
    object *players, *items;
    int count;

    players = get_players();
    items = get_items();

    output("\n");

    count = sizeof(players);
    if (count) {
        output(itemize(players));
        if (count > 1) {
            output(" are here.\n");
        } else {
            output(" is here.\n");
        }
    } else {
        output("No one is here.\n");
    }

    count = sizeof(items);
    if (count) {
        output("\n");
        output(itemize(items));
        if (count > 1) {
            output(" are here.\n");
        } else {
            output(" is here.\n");
        }
    }
}
