
#include <globals.h>

int main(string arg) {
    string *words = explode(arg, " ");
    string direction;
    string destination;
    string message;

    if (sizeof(words) != 2) {
        previous_object()->tell("Usage: add-exit <direction> <destination>\n");
        return 0;
    }

    direction = unabbreviate_direction(words[0]);
    destination = resolve_path(this_player()->query_cwd(), words[1]);

    if (here()->destination(direction)) {
        previous_object()->tell("That exit already exists.\n");
        return 0;
    }

    here()->add_exit(direction, destination);
    here()->set_grubby(1);

    message = sprintf("Made exit %s go to %s\n", direction, destination);
    previous_object()->tell(message);

    if (!load_object(destination)) {
        message = sprintf("Warning: destination %s could not be loaded.\n", destination);
        previous_object()->tell(message);
    }
    return 1;
}
