
#include <globals.h>

int save_room_to_data();
int save_room_to_room();
void usage();

int main(string arg) {

    if (!strlen(trim(arg))) {
        return save_room_to_data();
    }

    switch (trim(arg)) {
        case "t":
            return save_room_to_room();
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
    int datastat = save_room_to_data();
    int roomstat = here()->save_to_room();

    if (roomstat) {
        previous_object()->tell("Saved room to room file.\n");
    } else {
        previous_object()->tell("Error saving room to room file.\n");
    }

    return datastat && roomstat;
}

void usage() {
    int i1 = 4;
    int i2 = strlen("        't' - ");
    mixed *mess;
    mixed *m =
        ({ ({ "save-room [arg]\n", 0 }),
         ({ "    Where arg is:\n", i1 }),
         ({ "        't' - save the room's state to the room file itself, "
          "as well as to /data\n", i2
          }),
         ({ "        'h' - print this help\n", i2}),
         ({ "    With no args, just save the room object to /data\n", i1})
         });

    foreach (mess in m) {
        previous_object()->tell(mess[0], mess[1]);
    }
}
