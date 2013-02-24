
// Array of mappings
// ([ direction : attributes,
//    east : ([ file : "/domain/wiz/other" ])
//  ])
// attributes being a mapping
//     ([ file : "filename",
//        road : 1,
//        ... ])
private mapping exits;

mapping attributes(string direction);
void set_exits(mapping exs);
mapping get_exits();
void simple_set_exits(mapping exs);
string absolute_path(string file);
string *exit_directions();

string direction_to(object destination);
string destination(string direction);
int has_direction(string direction);
int is_road(string direction);

string glance_exits();
string description_exits();

void set_exits(mapping exs) {
    string k;
    mapping v;
    string direction;

    mapping exit_attributes;
    string attrib_key;
    mixed attrib_val;

    exits = ([ ]);

    foreach (k, v in exs) {
        direction = unabbreviate_direction(k);
        exit_attributes = ([ ]);

        foreach (attrib_key, attrib_val in v) {
            if (attrib_key == "file") {
                exit_attributes[attrib_key] = absolute_path(attrib_val);
            } else {
                exit_attributes[attrib_key] = attrib_val;
            }
        }
        exits[k] = exit_attributes;
    }
}

mapping get_exits() {
    return exits;
}

mapping attributes(string direction) {
    mapping r = 0;
    if (strlen(direction) && exits) {
        r = exits[direction];
    }

    return r;
}

int has_direction(string direction) {
    mixed v = attributes(direction);
    return v != 0;
}

void simple_set_exits(mapping exs) {
    string k;
    exits = ([ ]);
    if (exs) {
        foreach (k in keys(exs)) {
            exits[k] = ([ "file" : absolute_path(exs[k]) ]);
        }
    }
}

string absolute_path(string file) {
    return resolve_path(dirname(file_name(this_object())), file);
}

string *exit_directions() {
    if (exits) {
        return keys(exits);
    }
    return ({ });
}

string destination(string direction) {
    string r;
    mapping attribs = attributes(direction);
    if (attribs) {
        r = attribs["file"];
    }
    return r;
}

string direction_to(object place) {
    string dir;

    foreach (dir in exit_directions()) {
        if (destination(dir) == file_name(place)) {
            return as_place(dir);
        }
    }
    return "somewhere";
}

int is_road(string direction) {
    int r = 0;
    mapping exit = attributes(direction);
    if (exit) {
        r = exit["road"];
    }
    return r;
}

string glance_exits() {
    string *exits = exit_directions();
    string *abr;
    string r = "";
    int len = sizeof(exits);

    if (len) {
        abr = map(exits, (: abbreviate_direction($1) :));
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
