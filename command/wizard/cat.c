
#include <globals.h>

inherit "/inherit/command/multi-file";

string usage() {
    return "Usage: cat { <file> }";
}

void operate(string path) {
    cat(path);
}
