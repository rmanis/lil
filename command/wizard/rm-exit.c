
#include <globals.h>

int main(string args) {
    string *exits = explode(args, " ");
    string exit;
    string message;
    mapping result;

    if (!sizeof(exits)) {
        write("Usage: rm-exit <direction> [<direction>...]\n");
        return 0;
    }

    foreach (exit in exits) {
        result = here()->remove_exit(exit);
        message = sprintf( result ?  "Exit %s deleted.\n" :
                "There is no exit in the %s direction.\n",
                unabbreviate_direction(exit));
        previous_object()->tell(message);
    }

    return 1;
}
