
#include <globals.h>

mixed direct_get_obj(object obj, string ob_text);

mixed direct_get_obj(object obj, string ob_text) {
    return environment(obj) == environment(this_user());
}
