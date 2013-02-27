
#include <globals.h>

inherit "/inherit/command/multi-file";

string usage() {
    return "Usage: rmdir { <directory> }";
}

int condition(string path) {
    if (!rmdir(path)) {
        output("Could not remove %s.\n", path);
    }
    return 0;
}

void operate(string path) {
}
