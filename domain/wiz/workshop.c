#include <globals.h>

inherit ROOM_OB;

void create() {
    set_glance("Wizard workshop");
    set_description("You are here.");
    simple_set_exits( ([ "north" : "/domain/wiz/side-room" ]) );
}

