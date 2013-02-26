
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string *words;
    string target;
    string msg;
    object player;
    object user;

    string prefix1;
    string prefix2;

    if (!arg || !strlen(arg)) {
        return error_out("Usage: tell <player> <message>");
    }

    words = explode(arg, " ");
    target = words[0];
    msg = implode(words[1..], " ");

    foreach (user in users()) {
        if (user->query_name() == target) {
            player = user;
        }
    }

    if (!player) {
        return error_out(sprintf("%s is not logged in.", target));
    }

    if (player == this_player()) {
        prefix1 = "You tell yourself: ";
        this_player()->tell(sprintf(color_surround("red", "%s%s\n"), prefix1, msg),
                strlen(prefix1));
    } else if(!strlen(msg)) {
        error_out(sprintf("Tell %s what?", player->query_name()));
    } else {
        prefix1 = sprintf("You tell %s: ", player->query_name());
        prefix2 = sprintf("%s tells you: ", this_player()->query_name());
        this_player()->tell(color_surround("red", sprintf("%s%s\n", prefix1, msg)));
        msg = sprintf("%s%s\n", prefix2, msg);
        player->tell(color_surround("red", msg), strlen(prefix2));
    }

    return 1;
}
