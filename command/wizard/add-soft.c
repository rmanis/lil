
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string trimmed = trim(arg);
    string *words = explode(trimmed, " ");
    string soft;
    string description;

    if (sizeof(words) < 2) {
        return error_out("Usage: add-soft <object> <object description>");
    }

    soft = words[0];
    description = implode(words[1..], " ");

    here()->add_soft_object(soft, description);
    here()->set_grubby(1);
    here()->parse_refresh();

    previous_object()->tell("Added soft object.\n");

    return 1;
}
