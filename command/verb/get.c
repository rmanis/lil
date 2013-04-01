
#include <globals.h>

inherit VERB_OB;

int can_get_obj();
void do_get_obj(object obj, string obj_text);

void create() {
    parse_init();
    add_rules(({ "OBJ" }), ({ "take" }));
}

int can_get_obj() { return 1; }

void do_get_obj(object obj, string obj_text) {
    MESSAGE_D->targeted_action(previous_object(), "$N $vget $t.\n", obj);
    obj->move(previous_object());
}
