
inherit "/inherit/itemize";

object *interactive_in_array(object *arr, int value);
void write_occupants();

object *interactive_in_array(object *arr, int value) {
    int playercount = 0;
    object o;
    object *ret;

    foreach (o in arr) {
        if (interactive(o) == value) {
            playercount++;
        }
    }
    ret = allocate(playercount);
    foreach (o in arr) {
        if (interactive(o) == value) {
            playercount--;
            ret[playercount] = o;
        }
    }
    return ret;
}

void write_occupants() {
    object *occupants = all_inventory(this_object());
    object *players, *items;
    int count = sizeof(occupants);

    players = interactive_in_array(occupants, 1);
    items = interactive_in_array(occupants, 0);

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
    if (sizeof(items)) {
        write("\n");
        write(itemize(items));
        if (count > 1) {
            write(" are here.\n");
        } else {
            write(" is here.\n");
        }
    }
}
