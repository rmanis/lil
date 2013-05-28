
#include <globals.h>

inherit BASE;

// The base item object

mixed direct_get_obj(object obj, string ob_text);
mixed direct_drop_obj(object obj, string ob_text);

mixed direct_get_obj(object obj, string ob_text) {
    return 1;
}

mixed direct_drop_obj(object obj, string ob_text) {
    return 1;
}
