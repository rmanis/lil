
#include <globals.h>

inherit "/inherit/command/multi-file";

string usage() {
    return "Usage: rm { <file> }";
}

int condition(string path) {
    if (!rm(path)) {
        output("Could not remove %s.\n", path);
    }
    return 0;
}

void operate(string path) {
}
