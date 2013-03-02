
#include <globals.h>

inherit "/inherit/command/multi-file";

string usage() {
    return "Usage: update { <file> }";
}

void operate(string path) {
    object obj;
    int exists;
    if (!(sizeof(stat(path + ".c")) || sizeof(stat(path)))) {
        exists = 0;
        previous_object()->tell(sprintf("%s does not exist.\n", path));
    } else {
        exists = 1;
    }

    if (obj = find_object(path)) {
        destruct(obj);
    }

    if (!load_object(path) && exists) {
        previous_object()->tell(sprintf("Could not update %s\n", path));
    }
}

int condition(string path) {
    return find_object(path) != 0 || sizeof(stat(path + ".c"));
}
