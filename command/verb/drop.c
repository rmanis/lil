
#include <globals.h>

inherit VERB_OB;

int can_drop_obj();
void do_drop_obj(object obj, string obj_text);

void create() {
    parse_init();
    add_rules(({ "OBJ" }));
}

int can_drop_obj() { return 1; }

void do_drop_obj(object obj, string obj_text) {
    if (environment(obj) == previous_object()) {
        MESSAGE_D->targeted_action(previous_object(), "$N $vdrop $t.\n", obj);
        obj->move(environment(previous_object()));
    }
}
