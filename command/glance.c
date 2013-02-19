
#include <globals.h>

int main(string thing) {
    object room;

    if (strlen(thing) > 0) {
	write("You can't glance at things yet.\n");
    } else {
	room = environment(this_player());

	if (room) {
	    room->write_glance();
	} else {
	    output("Nowhere []\n");
	}
    }
}
