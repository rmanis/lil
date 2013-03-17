#include <globals.h>

inherit ROOM_OB;

void create() {
    ::create();
    set_glance("Wizard workshop");
    set_description("You are in the wizards workshop.  It is mostly empty, "
            "but you can feel a strange and strong magical presence here.  "
            "There is an archway leading into a room to the north.");
    simple_set_exits( ([ "north" : "/domain/wiz/side-room" ]) );
}

