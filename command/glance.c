
#include <globals.h>

int main(string thing) {
    object room;

    if (strlen(thing) > 0) {
	write("You can't glance at things yet.\n");
    } else {
	room = environment(this_player());

	if (room) {
	    // Maybe call something on the room to get the exits and whatnot.
	    write(room->get_glance() + "\n");
	} else {
	    write("Nowhere.\n");
	}
    }
}
