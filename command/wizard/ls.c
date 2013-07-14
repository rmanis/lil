
#include <globals.h>

inherit __DIR__ "lso";

string *fetch(string file) {
    string obname;
    if (filep(file)) {
        obname = dirname(file) + "/" + basename(file, ".c");
        return ({ basename(file) });
    } else {
        return ({ basename(file) + "/" });
    }
}
