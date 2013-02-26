#include <command.h>

#ifdef __NO_ENVIRONMENT__
#define say(x) shout(x)
#endif

int main(string arg)
{
    object sayer = this_player();
    string second_prefix = "You say: ";
    string third_prefix = sprintf("%s says: ", sayer->query_name());
    string third = sprintf("%s%s\n", third_prefix, arg);

    sayer->tell(sprintf("%s%s\n", second_prefix, arg));
    tell_room(environment(sayer), third, ({ sayer }), strlen(third_prefix));
    return 1;
}
