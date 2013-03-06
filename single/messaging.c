
#include <globals.h>

void tell(object o, string message);

string compose_message(object hearer, object doer, string action,
        object *objs);

void simple_action(object doer, string action, object *objs);
void targeted_action(object doer, string action, object *objs);
void my_action(object doer, string action, object *objs);
void other_action(object doer, string action, object *objs);

void tell(object o, string message) {
    o->tell(message);
}

// Grammar notes:
//  accusative - direct object
//  nominative - subject
//  reflexive - "himself"
//
// Message grammar specifiers:
//  $N - Nominative, the doer
//  $v - verb

string compose_message(object hearer, object doer, string action,
        object *objs) {
    int i;
    string msg = "";
    string verb;
    string target;
    mixed *fmt = reg_assoc(action, ({ "\\$[Nvt][A-Za-z]*" }), ({ 1 }));
    int num_objs = sizeof(objs);
    fmt = fmt[0][1..];

    for (i = 0; i < sizeof(fmt); i++) {
        if (!strlen(fmt[i])) {
            continue;
        }
        if (!(fmt[i][0] == '$' && strlen(fmt[i]) > 1)) {
            msg += fmt[i];
            continue;
        }
        // fmt[i] is an interpretable token
        switch (fmt[i][1]) {
            case 'N':
                msg += (hearer == doer ? "You" : doer->query_nominitive());
                break;
            case 'v':
                verb = fmt[i][2..];
                msg += (hearer == doer ? verb : pluralize(verb));
                break;
            case 't':
                if (i < num_objs) {
                    target = objs[i]->to_string();
                    msg += target;
                }
                break;
        }
    }
    return msg;
}

// Simple action.
// Involves the subject and maybe some things.
// "$N $vverb $A
//
// Tell the doer "You verb <thing>"
// Tell those in the same room as doer and those in the same room
//     as thing "<doer> verbs <thing>"
void simple_action(object doer, string action, object *objs) {
    string msg_doer;
    string msg_others;
    object room = environment(doer);

    msg_doer = compose_message(doer, doer, action, objs);
    msg_others = compose_message(0, doer, action, objs);

    tell(doer, msg_doer);
    tell_room(room, msg_others, ({ doer }));
}

// Targeted action
// involves the subject and maybe other players.
void targeted_action(object doer, string action, object *objs) {
}

void my_action(object doer, string action, object *objs) {
    string msg = compose_message(doer, doer, action, objs);
    tell(doer, msg);
}

void other_action(object doer, string action, object *objs) {
    string msg = compose_message(0, doer, action, objs);
    object room = environment(doer);

    tell_room(room, msg, ({ doer }));
}
