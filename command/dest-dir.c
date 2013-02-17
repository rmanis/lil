#include <globals.h>
#include <command.h>

int error_out(string str);

int main(string arg) {
    object here = here();
    string target;
    object target_ob;

    if (!arg) {
        return error_out("usage: dest-dir object");
    }

    if (here) {
        target = here->destination(unabbreviate_direction(arg));
        if (target) {
            target_ob = find_object(target);
        } else {
            return error_out("Nothing in that direction");
        }

        if (target_ob) {
            printf("Destructing %O\n", target_ob);
            target_ob->remove();
            if(target_ob) {
                destruct(target_ob);
            }
        } else {
            printf("Nothing to destruct.\n");
        }
    }

    return 0;
}

int error_out(string str) {
#ifndef __NO_ADD_ACTION__
        return notify_fail(str + "\n");
#else
        write(str + "\n");
        return 1;
#endif
}
