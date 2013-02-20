#include <command.h>

#ifdef __NO_ENVIRONMENT__
#define say(x) shout(x)
#endif

int main(string arg)
{
    object sayer = this_player();
    string second_prefix = "You say: ";
    string third_prefix = sprintf("%s says: ", sayer->query_name());
    string third = c_format(strlen(third_prefix), "%s%s\n",
            third_prefix, arg);

    c_output(strlen(second_prefix), "%s%s\n", second_prefix, arg);
    tell_room(environment(this_player()), third, ({ sayer }));
    return 1;
}
