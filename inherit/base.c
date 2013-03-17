
#include <globals.h>

void remove();
int move(mixed dest);
void set_ids(string *arg);
int id(string arg);
varargs void tell(string str, int indent);
string query_name();
string query_nominitive();
string query_reflexive();
string to_string();

string *parse_command_id_list();

// set to 'private static' so that inheritor won't be able to directly
// access this variable and so that save_object() won't save it to the .o file

string *ids;

private static string *parse_ids;
private static string *parse_plural_ids;

void create() {
    parse_init();
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
    return basename(file_name(this_object()));
}

string query_nominitive() {
    return query_name();
}

string query_reflexive() {
    return "itself";
}

string to_string() {
    return query_name();
}

// NLP applies

string *parse_command_id_list() {
    return parse_ids || ({ to_string() });
}

string *parse_command_plural_id_list() {
    return parse_plural_ids || ({ pluralize(to_string()) });
}
