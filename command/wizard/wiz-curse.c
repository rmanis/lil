

#include <globals.h>

inherit "/inherit/command/multi-user";

void operate(object user) {
    WIZ_D->curse(user);
}

string usage() {
    return "Usage: wiz-curse { username }";
}
