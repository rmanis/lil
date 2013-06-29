
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
mapping query_exits();
void simple_set_exits(mapping exs);
mapping remove_exit(string direction);
varargs mapping add_exit(string direction, string destination);
string absolute_path(string file);
string *exit_directions();

string direction_to(object destination);
string destination(string direction);
int has_direction(string direction);
int is_road(string direction);

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

mapping query_exits() {
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

mapping remove_exit(string direction) {
    string real_direction = unabbreviate_direction(direction);
    if (real_direction && exits[real_direction]) {
        map_delete(exits, real_direction);
    } else {
        return 0;
    }
    return exits;
}

varargs mapping add_exit(string direction, string destination, int road) {
    string real_direction = unabbreviate_direction(direction);
    if (direction && destination) {
        exits[real_direction] = ([ "file" : absolute_path(destination),
                "road" : road ]);
    }
    return exits;
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
