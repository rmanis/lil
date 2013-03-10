
#include <globals.h>

inherit "/inherit/command/multi-file";

string usage() {
    return "Usage: mkdir { <directory> }";
}

int condition(string path) {
    if (!mkdir(path)) {
        previous_object()->tell(sprintf("%s already exists.\n", path));
    }
    return 0;
}

void operate(string path) {
}
