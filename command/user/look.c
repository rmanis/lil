
#include <globals.h>

int main(string arg) {
    mixed *things;
    mixed thing;
    if (strlen(arg) > 0) {
        things = PICK_D->parse_names_for_player(previous_object(), arg);
        foreach (thing in things) {
            if (stringp(thing)) {
                MESSAGE_D->tell(previous_object(), "You don't see a " +
                        thing + " here.\n");
            } else {
                MESSAGE_D->targeted_action(previous_object(),
                        "$N $vlook at $t.\n", thing);
                // TODO: tell the looker what he sees.
            }
        }
    } else {
        LOOK_D->player_look(previous_object());
    }
}
