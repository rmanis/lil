
#include <globals.h>

mixed direct_give_obs_to_obj(object *obs, object obj, string obs_text, string ob_text);
mixed direct_give_obj_to_obj(object item, object receiver, string item_text, string receiver_text);

mixed direct_give_obs_to_obj(object *obs, object obj, string obs_text, string ob_text) {
    mixed *results = map(obs, (: direct_give_obj_to_obj :), obj, obs_text, ob_text);
    string *strings;

    strings = filter(results, (: stringp($1) :));

    if (sizeof(strings)) {
        return implode(strings, "\n");
    }
    return 1;
}

mixed direct_give_obj_to_obj(object item, object receiver, string item_text, string receiver_text) {
    return environment(item) == this_user();
}
