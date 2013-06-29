
#include <globals.h>

int main(string arg) {
    int input;

    if (!strlen(arg)) {
        previous_object()->tell(sprintf("Height: %d\n",
                        this_player()->query_print_height()));
    } else {
        sscanf(arg, "%d", input);

        if (input > 1) {
            this_player()->set_print_height(input);
            previous_object()->tell(sprintf("New height: %d\n",
                        this_player()->query_print_height()));
        }
    }
    return 1;
}
