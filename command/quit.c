#include <command.h>

#ifdef __NO_ENVIRONMENT__
#define say(x) shout(x)
#endif

int
main(string arg)
{
    previous_object()->tell("Bye.\n");
    this_player()->quit();
    say((string)previous_object()->query_name()
        + " leaves this reality.\n");
    previous_object()->remove();
    return 1;
}
