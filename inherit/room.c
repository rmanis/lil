
#include <globals.h>

// Array of players
private object *occupants;

// Array of mappings
// ([ direction : attributes,
//    east : ([ file : "/domain/wiz/other" ])
//  ])
// attributes being a mapping
//     ([ file : "filename",
//        road : 1,
//        ... ])
private mapping exits;

void set_glance(string desc);
void set_description(string desc);
string get_glance();
string get_description();

void set_exits(mapping exs);

mapping attributes(string direction);
string destination(string direction);
int is_road(string direction);
int has_direction(string direction);
string *exit_directions();
string glance_exits();
string description_exits();

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

void set_exits(mapping exs) {
    exits = exs;
}

void simple_set_exits(mapping exs) {
    string k;
    exits = ([ ]);
    if (exs) {
	foreach (k in keys(exs)) {
	    exits[k] = ([ "file" : exs[k] ]);
	}
    }
}

mapping attributes(string direction) {
    mapping r = 0;
    if (strlen(direction) && exits) {
	r = exits[direction];
    }

    return r;
}

string destination(string direction) {
    string r;
    mapping attribs = attributes(direction);
    if (attribs) {
	r = attribs["file"];
    }
    return r;
}

int is_road(string direction) {
    int r = 0;
    mapping exit = attributes(direction);
    if (exit) {
	r = exit["road"];
    }
    return r;
}

string *exit_directions() {
    if (exits) {
	return keys(exits);
    }
    return ({ });
}

string glance_exits() {
    string *exits = exit_directions();
    string *abr;
    string r = "";
    int len = sizeof(exits);
    int i;

    if (len) {
	abr = map(exits, "abbreviate_direction", "/single/simul_efun");
	r = "[" + implode(abr, ",") + "]";
    } else {
	r = "[]";
    }

    return r;
}

string look_exits() {
    string *exits = exit_directions();
    if (exits && sizeof(exits)) {
	return "Exits: " + implode(exits, ", ");
    }
    return "There are no obvious exits.";
}

int has_direction(string direction) {
    mixed v = attributes(direction);
    return v != 0;
}

void write_glance() {
    write(get_glance() + " " + glance_exits());
    write("\n");
}

void write_look() {
    write(get_description() + "\n");
    write(look_exits());
    write("\n");
}
