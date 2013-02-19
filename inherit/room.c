
#include <globals.h>
inherit __DIR__ "room/occupants";
inherit __DIR__ "room/exits";

void set_glance(string desc);
void set_description(string desc);
string get_glance();
string get_description();

void write_glance();
void write_look();

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

void write_glance() {
    output("%s %s", get_glance(), glance_exits());
    write_occupants();
}

void write_look() {
    output("%s\n", get_description());
    output(look_exits());
    write_occupants();
}
