
#include <globals.h>

int save_room_to_data();
int save_room_to_room();
int save_room_to_both();
void usage();

int main(string arg) {

    switch (trim(arg)) {
        case "r":
            return save_room_to_room();
            break;
        case "d":
            return save_room_to_data();
            break;
        case "b":
            return save_room_to_both();
            break;
        default:
            usage();
            break;
    }
    return 1;
}

int save_room_to_data() {

    if (here()->save_to_data()) {
        previous_object()->tell("Saved room to /data.\n");
        here()->set_grubby(0);
    } else {
        previous_object()->tell("Error saving room to /data.\n");
        return 0;
    }

    return 1;
}

int save_room_to_room() {

    string fname = file_name(here());
    if (here()->save_to_room()) {
        previous_object()->tell("Saved room to " + fname + ".\n");
    } else {
        previous_object()->tell("Error saving room to " + fname + ".\n");
        return 0;
    }

    return 1;
}

int save_room_to_both() {
    int datastat = save_room_to_data();
    int roomstat = save_room_to_room();

    return datastat && roomstat;
}

void usage() {
    mixed *mess;
    mixed *m =
        ({
         ({ "", "save-room <arg>\n" }),
         ({ "    ", "Where <arg> is:\n" }),
         ({ "        'r' - ",
          "save the room's state to the room file itself\n" }),
         ({ "        'd' - ", "save the room's state to /data\n" }),
         ({ "        'b' - ",
          "save the room's state to /data and the room file\n" }),
         ({ "        other - ", "print this help\n" }),
         });

    foreach (mess in m) {
        previous_object()->tell(mess[0] + mess[1], strlen(mess[0]));
    }
}
