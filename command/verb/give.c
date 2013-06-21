
#include <globals.h>

inherit VERB_OB;

void create() {
    parse_init();
    add_rules(({ "OBS to OBJ" }));
}

int can_give_obs_to_obj() { return 1; }
int can_give_obj_to_obj() { return 1; }

void do_give_obj_to_obj(object obj, object receiver) {
    if (environment(obj) == previous_object()) {
        MESSAGE_D->targeted_action(previous_object(), "$N $vgive $t to $o.\n", obj, ({ receiver }));
        obj->move(receiver);
    }
}

void do_give_obs_to_obj(object *obs, object obj) {
    foreach (object item in obs) {
        do_give_obj_to_obj(item, obj);
    }
}
