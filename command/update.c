
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
        output(path + " does not exist.\n");
    } else {
        exists = 1;
    }

    if (obj = find_object(path)) {
        destruct(obj);
    }

    if (!load_object(path) && exists) {
        output("Could not update " + path + "\n");
    }
}

int condition(string path) {
    return find_object(path) != 0 || sizeof(stat(path + ".c"));
}
