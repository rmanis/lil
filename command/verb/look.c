
#include <globals.h>

inherit VERB_OB;
inherit "/inherit/itemize";

int can_look();
int can_look_at_obs();
int can_look_at_str();
int can_look_obj();
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
    add_rules(({ "", "OBS", "at OBJ", "at OBS" }));
}

int can_look() { return 1; }
int can_look_at_obs() { return 1; }
int can_look_at_str() { return 1; }
int can_look_obj() { return 1; }
int can_look_obs() { return 1; }

void do_look() {
    LOOK_D->player_look(previous_object());
}

void do_look_obj(object obj, string obj_text) {
    MESSAGE_D->targeted_action(previous_object(),
            "$N $vlook at $t.\n", obj, 0);
    previous_object()->tell(obj->query_look_description() + "\n");
}

void do_look_obs(object *objs, string objs_text) {
    object ob;
    string target_text = itemize(objs->query_target_string());

    DEB(objs->to_string());
    MESSAGE_D->simple_action(previous_object(),
            "$N $vlook at " + target_text + ".\n", objs);

    foreach (ob in objs) {
        previous_object()->tell(ob->query_look_description() + "\n");
    }
}

void do_look_at_obs(object *objs, string objs_text) {
    do_look_obs(objs, objs_text);
}
