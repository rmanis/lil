#include <command.h>

int
main(string arg)
{
    object u;
    foreach (u in users()) {
        u->save();
    }
    shutdown(0);
    return 1;
}
