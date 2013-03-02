
#include <globals.h>

#ifdef __NO_ADD_ACTION__
object find_player(string name);

object find_player(string name) {
    object u;

    foreach (u in users()) {
        if (u->query_name() == name) {
            return u;
        }
    }
}
#endif
