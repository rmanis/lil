#include <globals.h>

inherit ROOM_OB;

void create() {
    ::create();
    set_glance(GLANCE);
    set_description("This is a new room.  Someone should describe it.");
    simple_set_exits( ([
                // "north" : "destination"
                ]) );
}
