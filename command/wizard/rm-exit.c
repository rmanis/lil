
#include <globals.h>

int main(string args) {
    string *exits = explode(args, " ");
    string exit;
    string fmt;
    string message;
    mapping result;

    if (!sizeof(exits)) {
        write("Usage: rm-exit <direction> [<direction>...]\n");
        return 0;
    }

    foreach (exit in exits) {
        result = here()->remove_exit(exit);
        if (result) {
            fmt = "Exit %s deleted.\n";
            here()->set_grubby(1);
        } else {
            fmt = "There is no exit in the %s direction.\n";
        }
        message = sprintf(fmt, unabbreviate_direction(exit));
        previous_object()->tell(message);
    }

    return 1;
}
