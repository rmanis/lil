
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string *parts = explode(arg, " ");
    string alias;

    if (!sizeof(parts)) {
        return error_out("Usage: unalias { <alias> }");
    }

    foreach (alias in parts) {
        if (!previous_object()->query_alias(alias)) {
            previous_object()->tell(sprintf("Alias '%s' is undefined.\n", alias));
        } else {
            map_delete(previous_object()->query_aliases(), alias);
            previous_object()->tell(sprintf("Alias '%s' deleted.\n", alias));
        }
    }
    return 1;
}
