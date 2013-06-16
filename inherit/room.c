
#include <globals.h>

inherit BASE;
inherit __DIR__ "room/occupants";
inherit __DIR__ "room/exits";

void set_glance(string desc);
void set_description(string desc);
void add_soft_object(string name, string desc);
string query_soft_description(string name);
string query_look_description();
string get_glance();
string get_description();
varargs void tell(string msg, int indent);

private string glance;
private string description;
private mapping soft_objects = ([ ]);

void create() {
    ::create();
    set_parse_ids(({ "here", "room", file_name() }));
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

void add_soft_object(string name, string desc) {
    if (strlen(name) && strlen(desc)) {
        soft_objects[name] = desc;
    }
}

string query_soft_description(string name) {
    return soft_objects[name];
}

string query_look_description() {
    return "This is a room.\n" + get_description();
}

string get_glance() {
    return glance;
}

string get_description() {
    return description;
}

string *parse_command_id_list() {
    return ::parse_command_id_list() + keys(soft_objects);
}

mixed direct_look_obj(object obj, string ob_text) {
    return member_array(ob_text, parse_command_id_list()) >= 0;
}

varargs void tell(string msg, int indent) {
    object o;
    foreach (o in all_inventory()) {
        o->tell(msg, indent);
    }
}
