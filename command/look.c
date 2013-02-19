
#include <globals.h>

int main(string thing) {
    object room;

    if (strlen(thing) > 0) {
	output("You can't look at things yet.\n");
    } else {
	room = environment(this_player());

	if (room) {
	    room->write_look();
	} else {
	    output("You don't seem to be anywhere, really.\n");
	}
    }
}
