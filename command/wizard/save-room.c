
#include <globals.h>

int main(string arg) {
    if (here()->save_to_data()) {
        previous_object()->tell("Saved room.\n");
        here()->set_grubby(0);
    } else {
        previous_object()->tell("Error saving room.\n");
        return 0;
    }

    return 1;
}
