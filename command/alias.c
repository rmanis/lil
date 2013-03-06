
#include <globals.h>

void print_aliases();
void print_alias(string alias);

int main(string arg) {
    string *parts = explode(arg, " ");
    string key;
    string value;
    string old_alias;
    string msg;

    if (!strlen(arg)) {
        print_aliases();
    } else if (sizeof(parts) == 1) {
        print_alias(parts[0]);
    } else {
        key = parts[0];
        value = implode(parts[1..], " ");

        old_alias = previous_object()->get_alias(key);

        if (old_alias) {
            msg = sprintf("Changing alias '%s'\n", key);
            previous_object()->tell(msg);
            msg = sprintf(" from: %s\n", old_alias);
            previous_object()->tell(msg, 7);
            msg = sprintf(" to:   %s\n", value);
            previous_object()->tell(msg, 7);
        } else {
            msg = sprintf("Adding alias '%s' as '%s'\n", key, value);
            previous_object()->tell(msg);
        }
        previous_object()->set_alias(key, value);
    }
    return 1;
}

void print_aliases() {
    string k, v;
    int longest = 0;
    int len;
    string fmt;

    mapping aliases = previous_object()->get_aliases();
    string *keys = keys(aliases);

    if (!sizeof(aliases)) {
        previous_object()->tell("No aliases defined.\n");
        return;
    }

    foreach (k, v in aliases) {
        len = strlen(k);
        if (len > longest) {
            longest = len;
        }
    }
    foreach (k in sort_array(keys, 1)) {
        v = aliases[k];
        width = longest - strlen(k);
        previous_object()->tell(sprintf("%s%" + width + "s : %s", k, "", quoted(v)));
    }
}

void print_alias(string alias) {
    string value = previous_object()->get_alias(alias);
    string msg;

    if (value) {
        msg = sprintf("Alias '%s' : '%s'\n", alias, value);
    } else {
        msg = sprintf("Alias '%s' is undefined.\n", alias, value);
    }

    previous_object()->tell(msg);
}
