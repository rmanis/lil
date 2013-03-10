
#include <globals.h>

inherit "/inherit/command/multi-user";

void operate(object user) {
    WIZ_D->bless(user);
}

string usage() {
    return "Usage: wiz-bless { username }";
}
