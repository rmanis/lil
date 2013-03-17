#include <globals.h>

inherit ROOM_OB;

void create() {
    ::create();
    set_glance("Side room");
    set_description("You are in an empty room.  The wizards' workshop is through the doorway to the south.");
    simple_set_exits( ([ "south" : "/domain/wiz/workshop" ]) );
}

