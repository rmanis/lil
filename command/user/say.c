#include <command.h>

#ifdef __NO_ENVIRONMENT__
#define say(x) shout(x)
#endif

int main(string arg)
{
    object sayer = this_player();
    string second_prefix = "You say: ";
    string second = sprintf("%s%s\n", second_prefix, arg);
    string third_prefix = sprintf("%s says: ", sayer->query_name());
    string third = sprintf("%s%s\n", third_prefix, arg);

    string m2 = color_surround("cyan", second);
    string m3 = color_surround("cyan", third);

    sayer->tell(m2);
    tell_room(environment(sayer), m3, ({ sayer }), strlen(third_prefix));
    return 1;
}
