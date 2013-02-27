
#include <globals.h>

inherit "/inherit/command/multi-file";

string usage() {
    return "Usage: touch { <file> }";
}

int condition(string path) {
    return !sizeof(stat(path));
}

void operate(string path) {
    ensure_path_of_file_exists(path);
    write_file(path, "");
}
