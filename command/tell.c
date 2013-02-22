
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string *words;
    string target;
    string msg;
    object player;
    object user;

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
        return error_out(format("%s is not logged in.", target));
    }

    if (player == this_player()) {
        tell_object(this_player(), format("%^RED%^You tell yourself: %s\n%^RESET%^", msg));
    } else if(!strlen(msg)) {
        error_out(format("Tell %s what?", player->query_name()));
    } else {
        this_player()->tell(color_surround("red", sprintf("You tell %s: %s\n", player->query_name(), msg)));
        msg = sprintf("%s tells you: %s\n", this_player()->query_name(), msg);
        player->tell(color_surround("red", msg));
    }

    return 1;
}
