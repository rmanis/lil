
#include <globals.h>

int main(string arg) {
    int input;

    if (!strlen(arg)) {
        output("Height: %d\n", this_player()->get_print_height());
    } else {
        sscanf(arg, "%d", input);

        if (input > 1) {
            this_player()->set_print_height(input);
            output("New height: %d\n", this_player()->get_print_height());
        }
    }
    return 1;
}
