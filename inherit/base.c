
#include <globals.h>

mixed fetch_variable(string variable);
void store_variable(string variable, mixed value);
varargs int save_object(string name, int flags);
void create();
void setup();
int save_to_data();
int load_from_data();
void remove();
int move(mixed dest);
void set_ids(string *arg);
int id(string arg);
varargs void tell(string str, int indent);
string query_name();
string query_in_room_name();
string query_target_string();
string query_indefinite();
string query_nominitive();
string query_reflexive();
string query_look_description();
string to_string();

void p_refresh();
int inventory_accessible();
int inventory_visible();
string *parse_command_id_list();
string *parse_command_plural_id_list();
mixed direct_look_obj(object obj, string ob_text);
mixed direct_look_at_obj(object obj, string ob_text);

// set to 'private static' so that inheritor won't be able to directly
// access this variable and so that save_object() won't save it to the .o file

string *ids;

static string look_description;

private static string *parse_ids;
private static string *parse_plural_ids;

mixed fetch_variable(string variable) {
    return efun::fetch_variable(variable);
}

void store_variable(string variable, mixed value) {
    efun::store_variable(variable, value);
}

varargs int save_object(string name, int flags) {
    return efun::save_object(name, flags);
}

void create() {
    parse_init();
    setup();
}

void setup() {
    look_description = "This is " + query_in_room_name() + ".";
}

string data_file_name() {
    return DATA_DIR + file_name();
}

int save_to_data() {
    ensure_path_of_file_exists(data_file_name());
    return save_object(data_file_name(), 0);
}

int load_from_data() {
    mixed err;
    int r;
    if (sizeof(stat(data_file_name() + ".o"))) {
        err = catch (r = restore_object(data_file_name()));
    }

    return r;
}

void remove() {
    // add code here to prevent unwanted destructions.
    // update attributes of the container and the containees.
    destruct(this_object());
}

#ifndef __NO_ENVIRONMENT__
int move(mixed dest) {
    // add code here to prevent disallowed moves (target is full, object
    // is immovable, etc.).
    move_object(dest);
}
#endif

void set_ids(string *arg) {
    // probably want to add some security here.
    ids = arg;
}

void set_parse_ids(string *names) {
    parse_ids = names;
}

void set_parse_plural_ids(string *names) {
    parse_plural_ids = names;
}

int id(string arg) {
    if (!arg || !ids) {
        return 0;
    }
    return (member_array(arg, ids) != -1);
}

varargs void tell(string str, int indent) {

}

string query_name() {
    string f = file_name();
    int index = member_array('#', f);
    if (index > 0) {
        f = f[0..index-1];
    }
    return basename(f);
}

string query_in_room_name() {
    return query_indefinite() + " " + query_name();
}

string query_target_string() {
    return "the " + query_name();
}

string query_indefinite() {
    string *vowels = ({ 'a', 'o', 'e', 'u', 'i' });
    int index = member_array(basename(query_name())[0], vowels);

    return "a" + (index >= 0 ? "n" : "");
}

string query_nominitive() {
    return query_name();
}

string query_reflexive() {
    return "itself";
}

string query_look_description() {
    return look_description;
}

string to_string() {
    return query_name();
}

// NLP applies

void p_refresh() {
    parse_refresh();
}

int inventory_accessible() {
    return 1;
}

int inventory_visible() {
    return 1;
}

string *parse_command_id_list() {
    return parse_ids || ({ to_string() });
}

string *parse_command_plural_id_list() {
    return parse_plural_ids || ({ pluralize(to_string()) });
}

mixed direct_look_obj(object obj, string ob_text) {
    return with_or_has(this_user(), obj) ||
        environment(this_user()) == obj;
}

mixed direct_look_at_obj(object obj, string ob_text) {
    return direct_look_obj(obj, ob_text);
}

