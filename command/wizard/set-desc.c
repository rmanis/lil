
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string trimmed = trim(arg);

    if (!strlen(trimmed)) {
        return error_out("Usage: set-description <new description string>");
    }

    trimmed = replace_string(trimmed, "\\t", "\t");
    trimmed = replace_string(trimmed, "\\n", "\n");
    trimmed = replace_string(trimmed, "\\\"", "\"");

    here()->set_description(trimmed);
    here()->set_grubby(1);

    previous_object()->tell("Description set.\n");

    return 1;
}
