
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string soft = trim(arg);
    string *words = explode(soft, " ");

    if (sizeof(words) != 1) {
        return error_out("Usage: rm-soft <soft-object>");
    }

    if (here()->remove_soft_object(soft)) {
        here()->set_grubby(1);
        here()->parse_refresh();
        previous_object()->tell(sprintf("Removed %s soft object\n", soft));
    } else {
        return error_out(sprintf("Soft object %s is not here.", soft));
    }

    return 1;
}
