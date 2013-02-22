#include <command.h>

inherit "/inherit/error_out";

int
main(string arg)
{
    object obj;

    if (!arg) {
        return error_out("usage: dest object");
    }
    obj = find_object(arg);
#ifndef __NO_ENVIRONMENT__
    if (!obj) {
        obj = present(arg);
        if (!obj) {
            obj = present(arg, environment(previous_object()));
        }
    }
#endif
    if (!obj) {
        return error_out("can't find that.\n");
    }
    obj->remove();
    if (obj) {
        destruct(obj);
    }
    return 1;
}
