#include <globals.h>

int main(string arg) {
    if (trim(arg) == "off") {
        this_player()->disable_autosave();
        this_player()->tell("Autosave disabled.\n");
    } else {
        this_player()->enable_autosave();
        this_player()->tell("Autosave enabled.\n");
    }
}

