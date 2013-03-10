
#include <globals.h>

int main(string thing) {
    if (strlen(thing) > 0) {
        previous_object()->tell("You can't look at things yet.\n");
    } else {
        LOOK_D->player_look(previous_object());
    }
}
