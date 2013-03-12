
// Master object NLP applies
string *parse_command_id_list();
string *parse_command_plural_id_list();
// string *parse_command_adjectiv_id_list();
string *parse_command_prepos_list();
string parse_command_all_word();
object *parse_command_users();
void p_refresh();

// Refers to anything
string *parse_command_id_list() {
    return ({ "thing", "something" });
}

// Refers to plural of anything
string *parse_command_plural_id_list() {
    return ({ "everything", "them", "things" });
}

// The driver might take care of these already?
// string *parse_command_adjectiv_id_list() {
//     return ({ "the", "a", "an" });
// }

string *parse_command_prepos_list() {
    return ({ "along", "at", "behind", "beside", "by", "from", "in", "inside",
            "into", "on", "onto", "under", "upon", "with", "within" });
}

string parse_command_all_word() {
    return "all";
}

// Refers to users that may not be in the same room.
// This gets cached, call p_refresh whenever someone logs in or out.
object *parse_command_users() {
    return users();
}


// Force the master to refresh parsing stuff.
void p_refresh() {
    parse_refresh();
}
