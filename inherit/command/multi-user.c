
#include <globals.h>

inherit "/inherit/error_out";

string usage();
void operate(object user);

int main(string arg) {
    string *usernames = explode(arg, " ");
    object *users = map(usernames, "find_player", "/single/simul_efun");
    int arg_count = usernames && sizeof(usernames);
    int i;

    if (!arg_count) {
        return error_out(usage());
    }

    for (i = 0; i < arg_count; i++) {
        if (users[i]) {
            operate(users[i]);
        } else {
            MESSAGE_D->tell(previous_object(), "Could not find user " + usernames[i] + "\n");
        }
    }

    return 1;
}
