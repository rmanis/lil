
#include <globals.h>

void tell(object o, string message);

string compose_message(object hearer, object doer, object target,
        string action, mixed *objs);

void simple_action(object doer, string action, mixed *objs);
void targeted_action(object doer, string action, object target, mixed *objs);
void my_action(object doer, string action, mixed *objs);
void other_action(object doer, string action, mixed *objs);

void tell(object o, string message) {
    if (o && strlen(message)) {
        o->tell(message);
    }
}

void announce(string message) {
    foreach (object u in users()) {
        u->tell(color_surround("bold", message));
    }
}

// Grammar notes:
//  accusative - direct object
//  nominative - subject
//  reflexive - "himself"
//
// Message grammar specifiers:
//  $N - Nominative, the doer
//  $v - verb
//  $t - target
//  $s - string

string compose_message(object hearer, object doer, object target,
        string action, mixed *objs) {
    int i;
    int j = 0;
    int o_i = 0;
    string msg = "";
    string verb;
    mixed *fmt = reg_assoc(action, ({ "\\$[NnvTtOoSs][A-Za-z]*" }), ({ 1 }));
    // int num_objs = sizeof(objs);
    fmt = fmt[0];

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
            case 'n':
                msg += (hearer == doer ? "you" : doer->query_nominitive());
                break;
            case 'v':
                verb = fmt[i][2..];
                msg += (hearer == doer ? verb : pluralize(verb));
                break;
            case 'T':
                if (target && target == hearer && target == doer) {
                    msg += "Yourself";
                } else if (target && hearer == target) {
                    msg += "You";
                } else if (target && target == doer) {
                    msg += target->query_reflexive();
                } else if (target) {
                    msg += target->query_target_string();
                }
                break;
            case 't':
                if (target && target == hearer && target == doer) {
                    msg += "yourself";
                } else if (target && hearer == target) {
                    msg += "you";
                } else if (target && target == doer) {
                    msg += target->query_reflexive();
                } else if (target) {
                    msg += target->query_target_string();
                }
                break;
            case 'O':
                msg += capitalize(objs[o_i]->to_string());
                o_i++;
                break;
            case 'o':
                msg += objs[o_i]->to_string();
                o_i++;
                break;
            case 'S':
                msg += capitalize(objs[o_i]);
                o_i++;
                break;
            case 's':
                msg += objs[o_i];
                o_i++;
                break;
        }
        j++;
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
void simple_action(object doer, string action, mixed *objs) {
    string msg_doer;
    string msg_others;
    object room = environment(doer);

    msg_doer = compose_message(doer, doer, 0, action, objs);
    msg_others = compose_message(0, doer, 0, action, objs);

    tell(doer, msg_doer);
    if (room) {
        tell_room(room, msg_others, ({ doer }));
    }
}

// Targeted action
// involves the subject, the target, and maybe other players.
void targeted_action(object doer, string action, object target, mixed *objs) {
    string msg_doer = compose_message(doer, doer, target, action, objs);
    string msg_target = compose_message(target, doer, target, action, objs);
    string msg_others = compose_message(0, doer, target, action, objs);
    object doer_room;
    object target_room;
    object *except = ({ doer, target });

    doer_room = doer ? environment(doer) : 0;
    target_room = target ? environment(target) : 0;

    if (doer_room) {
        tell(doer, msg_doer);
        if (target != doer && target != doer_room) {
            tell(target, msg_target);
        }
        if (doer_room) {
            tell_room(doer_room, msg_others, except);
            if (doer_room != target_room && target_room) {
                tell_room(target_room, msg_others, except);
            }
        }
    }
}

// Action that only the doer hears.
void my_action(object doer, string action, mixed *objs) {
    string msg = compose_message(doer, doer, 0, action, objs);
    tell(doer, msg);
}

// Action that everyone around the doer can hear, but the doer can't
void other_action(object doer, string action, mixed *objs) {
    string msg = compose_message(0, doer, 0, action, objs);
    object room = environment(doer);

    if (room) {
        tell_room(room, msg, ({ doer }));
    }
}
