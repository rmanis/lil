
#include <globals.h>
inherit __DIR__ "room/occupants";
inherit __DIR__ "room/exits";

void set_glance(string desc);
void set_description(string desc);
string get_glance();
string get_description();

private string glance;
private string description;

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
