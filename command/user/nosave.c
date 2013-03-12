
#include <globals.h>

int main(string arg) {

    if (trim(arg) == "off") {
        MESSAGE_D->tell(previous_object(), "Enabling autosave.\n");
        previous_object()->autosave();
    } else {
        MESSAGE_D->tell(previous_object(), "Disabling autosave.\n");
        previous_object()->disable_autosave();
    }
    return 1;
}
