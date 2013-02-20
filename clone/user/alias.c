
#include <globals.h>

mapping get_prefix(int arg);
mapping get_prefixes();
mapping new_prefixes();

mapping prefixes;

mapping get_prefix(int arg) {
    if (!prefixes) {
        prefixes = new_prefixes();
    }
    return prefixes[arg];
}

mapping get_prefixes() {
    if (!prefixes) {
        prefixes = new_prefixes();
    }
    return prefixes;
}

mapping new_prefixes() {
    return ([ '\'' : "say" ]);
}
