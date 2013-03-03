
#include <globals.h>

mapping get_prefix(int arg);
mapping get_prefixes();

mapping get_aliases();
string get_alias(string command);
void set_alias(string command, string alias);

mapping prefixes;
mapping aliases;

mapping get_prefix(int arg) {
    if (!prefixes) {
        prefixes = ALIAS_D->default_prefixes();
    }
    return prefixes[arg];
}

mapping get_prefixes() {
    if (!prefixes) {
        prefixes = ALIAS_D->default_prefixes();
    }
    return prefixes;
}

mapping get_aliases() {
    if (!aliases) {
        aliases = allocate_mapping(8);
    }
    return aliases;
}

string get_alias(string command) {
    return get_aliases()[command] || ALIAS_D->default_aliases()[command];
}

void set_alias(string command, string alias) {
    aliases[command] = alias;
}
