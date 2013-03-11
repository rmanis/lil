
#include <globals.h>

int main(string arg) {
    object *things;
    object thing;
    if (strlen(arg) > 0) {
        things = PICK_D->parse_names_for_player(previous_object(), arg);
        foreach (thing in things) {
            MESSAGE_D->targeted_action(previous_object(), "$N $vlook at $t.\n", thing);
            // TODO: tell the looker what he sees.
        }
    } else {
        LOOK_D->player_look(previous_object());
    }
}
