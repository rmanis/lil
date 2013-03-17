
#include <globals.h>

inherit BASE;
inherit __DIR__ "room/occupants";
inherit __DIR__ "room/exits";

void set_glance(string desc);
void set_description(string desc);
string get_glance();
string get_description();
varargs void tell(string msg, int indent);

private string glance;
private string description;

void create() {
    ::create();
    set_parse_ids(({ "here", file_name() }));
}

void setup() {
    set_glance("New room");
    set_description("This is a new room.  Someone should describe it.");
}

void set_glance(string desc) {
    glance = desc;
}

void set_description(string desc) {
    description = desc;
}

string get_glance() {
    return glance;
}

string get_description() {
    return description;
}

varargs void tell(string msg, int indent) {
    object o;
    foreach (o in all_inventory()) {
        o->tell(msg, indent);
    }
}
