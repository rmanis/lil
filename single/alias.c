
#include <globals.h>

mapping default_prefixes();
mapping default_aliases();

mapping default_prefixes() {
    return ([ '\'' : "say" ]);
}

mapping default_aliases() {
    return ([
            "l" : "look",
            "i" : "inventory",
            ]);
}
