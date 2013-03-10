
#include <globals.h>

#ifdef __NO_ADD_ACTION__
object find_player(string name);

object find_player(string name) {
    object u;

    foreach (u in users()) {
        if (u->query_name() == "/single/simul_efun/strings"->trim(name)) {
            return u;
        }
    }
}
#endif
