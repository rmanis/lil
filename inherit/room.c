
#include <globals.h>

inherit BASE;
inherit __DIR__ "room/occupants";
inherit __DIR__ "room/exits";

int query_grubby();
void set_grubby(int grubbiness);
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
private static int grubby = 0;

void create() {
    ::create();
    set_parse_ids(({ "here", "room", purename(basename(file_name())) }));
}

void setup() {
    set_glance("New room");
    set_description("This is a new room.  Someone should describe it.");
}

int query_grubby() {
    return grubby;
}

void set_grubby(int grubbiness) {
    grubby = grubbiness;
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
    string text = soft_objects[name];
    if (!text &&
            (name == "here" ||
             name == "room" ||
             name == purename(basename(file_name())))) {
        text = query_look_description();
    }
    return text;
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
