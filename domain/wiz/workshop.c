#include <globals.h>

inherit ROOM_OB;

void add_softs();

void create() {
    mapping attrib;

    ::create();

    set_glance("Wizard workshop");
    set_description("You are in the wizards workshop.  It is mostly empty, "
            "but you can feel a strange and strong magical presence here.  "
            "There is an archway leading into a room to the north.");
    simple_set_exits( ([ "north" : "/domain/wiz/side-room" ]) );
    attrib = attributes("north");

    add_softs();

    attrib[LEAVE] = "$N $vleave through the north archway.";
    attrib[ARRIVE] = "$N $varrive from the south, through the archway.";

    load_from_data();
}

void add_softs() {
    string arch = "This is an archway.  It is made of grey stone.  It is "
        "about nine feet tall and six feet wide at the base.";
    add_soft_object("arch", arch);
    add_soft_object("archway", arch);
}
