
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string trimmed = trim(arg);

    if (!strlen(trimmed)) {
        return error_out("Usage: set-glance <new glance string>");
    }

    here()->set_glance(trimmed);
    here()->set_grubby(1);

    previous_object()->tell("Glance string set.\n");

    return 1;
}
