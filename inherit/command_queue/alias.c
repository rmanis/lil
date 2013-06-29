
#include <globals.h>

mapping query_prefix(int arg);
mapping query_prefixes();

mapping query_aliases();
string query_alias(string command);
void set_alias(string command, string alias);

mapping prefixes;
mapping aliases;

mapping query_prefix(int arg) {
    if (!prefixes) {
        prefixes = ALIAS_D->default_prefixes();
    }
    return prefixes[arg];
}

mapping query_prefixes() {
    if (!prefixes) {
        prefixes = ALIAS_D->default_prefixes();
    }
    return prefixes;
}

mapping query_aliases() {
    if (!aliases) {
        aliases = allocate_mapping(8);
    }
    return aliases;
}

string query_alias(string command) {
    return query_aliases()[command] || ALIAS_D->default_aliases()[command];
}

void set_alias(string command, string alias) {
    aliases[command] = alias;
}
