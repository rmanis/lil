
#include <globals.h>

mixed indirect_give_obs_to_obj(object *items, object receiver);
mixed indirect_give_obj_to_obj(object item, object receiver);

mixed indirect_give_obs_to_obj(object *items, object receiver) {
    return 1;
}

mixed indirect_give_obj_to_obj(object item, object receiver) {
    return 1;
}
