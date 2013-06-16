
#include <globals.h>

void create() {
    call_out("save_users", SAVE_PERIOD);
}

void save_users() {
    foreach (object u in users()) {
        if (u->query_autosave()) {
            u->tell("%^CYAN%^Autosaving...%^RESET%^\n");
            u->save();
        }
    }
    call_out("save_users", SAVE_PERIOD);
}
