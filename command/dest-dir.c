#include <globals.h>
#include <command.h>

inherit "/inherit/error_out";

int main(string arg) {
    object here = here();
    string target;
    object target_ob;

    if (!arg) {
        return error_out("Usage: dest-dir <object>");
    }

    if (here) {
        target = here->destination(unabbreviate_direction(arg));
        if (target) {
            target_ob = find_object(target);
        } else {
            return error_out("Nothing in that direction");
        }

        if (target_ob) {
            previous_object()->tell(sprintf("Destructing %O\n", target_ob));
            target_ob->remove();
            if(target_ob) {
                destruct(target_ob);
            }
        } else {
            previous_object()->tell(sprintf("Nothing to destruct.\n");
        }
    }

    return 1;
}

