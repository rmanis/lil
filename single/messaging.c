
#include <globals.h>

void tell(object o, string message);

void tell(object o, string message) {
    o->tell(message);
}
