
#include <globals.h>
#include <parse_error.h>

// Master object NLP applies
string *parse_command_id_list();
string *parse_command_plural_id_list();
string *parse_command_adjectiv_id_list();
string *parse_command_prepos_list();
string parse_command_all_word();
object *parse_command_users();
string parser_error_message(int error, object ob, mixed arg, int plural);
void p_refresh();

// Refers to anything
string *parse_command_id_list() {
    return ({ "thing", "something" });
}

// Refers to plural of anything
string *parse_command_plural_id_list() {
    return ({ "everything", "them", "things" });
}

string *parse_command_adjectiv_id_list() {
    return ({ "the", "a", "an", "yon", "thy", "dat" });
}

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

string parser_error_message(int error, object ob, mixed arg, int plural) {
    switch (error) {
        case PARSE_NOT_HERE: /*  couldn't find a matching object */
            return "There is no " + arg + " here.\n";

        case PARSE_NOT_ALIVE: /* is_living() returned 0 for match for LIV token */
            if( plural )
                return "The " + pluralize(arg) + " are not alive.\n";
            else
                return "The " + arg + " isn't alive.\n";

        case PARSE_UNACCESSIBLE: /* inventory_accessible() returned 0 in container */
            if( plural )
                return "They are out of reach.\n";
            else
                return "It is out of your reach.\n";

        case PARSE_AMBIGUOUS: /* more than one object matched for a singular rule */
            return "Which of the " + arg +
                " do you mean?\n";

        case PARSE_WRONG_NUMBER: /* not enough matching objects found */
            arg = -arg - 1;
            if( arg > 1 )
                return "There are only " + sizeof(arg) + " of them.\n";
            else
                return "There is only one of them.\n";

        case PARSE_ALLOCATED:  /* no idea what this one is :) */
            return arg;

        case PARSE_NOT_FOUND: /* no matching object found */
            return "There is no " + arg + " here.\n";

        case PARSE_TOO_MANY: /* multiple objects matched for a singular rule? */
            return "You can only do that to one thing at a time.\n";

    }
}
