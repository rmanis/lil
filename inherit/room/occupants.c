
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

    write("\n");

    count = sizeof(players);
    if (count) {
        write(itemize(players));
        if (count > 1) {
            write(" are here.\n");
        } else {
            write(" is here.\n");
        }
    } else {
        write("No one is here.\n");
    }

    count = sizeof(items);
    if (count) {
        write("\n");
        write(itemize(items));
        if (count > 1) {
            write(" are here.\n");
        } else {
            write(" is here.\n");
        }
    }
}
