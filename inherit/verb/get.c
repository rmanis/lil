
#include <globals.h>

mixed direct_get_obj(object obj, string ob_text);

mixed direct_get_obj(object obj, string ob_text) {
    if (environment(obj) != environment(this_user())) {
        return "You can't get that.\n";
    }
    return 1;
}
