
#include <globals.h>

inherit VERB_OB;
inherit "/inherit/itemize";

int can_look();
int can_look_at_obs();
int can_look_at_str();
int can_look_obj();
int can_look_str();
int can_look_obs();

void do_look();
void do_look_at_obs(object *objs, string objs_text);
void do_look_obs(object *objs, string objs_text);
void do_look_obj(object obj, string obj_text);
void do_look_str(string text);
void do_look_at_str(string text);

void create() {
    parse_init();
    add_rules(({ "OBJ" }), ({ "examine" }));
    add_rules(({ "STR" }), ({ "examine" }));
    add_rules(({ "", "OBS", "at OBJ", "at OBS", "at STR" }));
}

int can_look() { return 1; }
int can_look_at_obs() { return 1; }
int can_look_at_str() { return 1; }
int can_look_obj() { return 1; }
int can_look_str() { return 1; }
int can_look_obs() { return 1; }

void do_look() {
    LOOK_D->player_look(previous_object());
}

void do_look_obj(object obj, string obj_text) {
    MESSAGE_D->targeted_action(previous_object(),
            "$N $vlook at $t.\n", obj, 0);
}

void do_look_obs(object *objs, string objs_text) {
    string target_text = itemize(objs->to_string());
    DEB(objs->to_string());
    MESSAGE_D->simple_action(previous_object(),
            "$N $vlook at " + target_text + ".\n", objs);
}

void do_look_at_obs(object *objs, string objs_text) {
    write("do_look_at_obs\n");
    DEB(objs);
    DEB(objs_text);
}

void do_look_at_str(string text) { do_look_str(text); }

void do_look_str(string text) {
    string *things = PICK_D->parse_list(text);

    foreach (string thing in things) {
        previous_object()->execute(sprintf("look %s", thing));
    }
}
