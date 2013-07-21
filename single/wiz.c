
#include <globals.h>

void bless(object user);
void curse(object user);

void bless(object user) {

    if (user && !user->query_wizard()) {
        user->set_wizard(1);
        ensure_path_of_file_exists(user_cwd(user->query_name()) + "/.");

        MESSAGE_D->announce(user->query_name() + " is become wizard.\n");
    }
}

void curse(object user) {
    if (user && user->query_wizard()) {
        user->set_wizard(0);

        MESSAGE_D->announce(user->query_name() + " is cursed to be mortal.\n");
    }
}
