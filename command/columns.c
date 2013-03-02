
#include <globals.h>

int main(string arg) {
    int input;

    if (!strlen(arg)) {
        previous_object()->tell(sprintf("Width: %d\n", this_player()->get_print_width()));
    } else {
        sscanf(arg, "%d", input);

        if (input > 1) {
            this_player()->set_print_width(input);
            previous_object()->tell(sprintf("New width: %d\n", this_player()->get_print_width()));
        }
    }
    return 1;
}
