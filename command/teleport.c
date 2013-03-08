
#include <globals.h>

inherit "/inherit/error_out";

string usage();
int teleport_to(string place);
int teleport_player(string player, string place);
int teleport(object player, object place);

int main(string args) {
    string *words;

    if (!args) {
        return 0;
    }

    words = explode(args, " ");
    switch (sizeof(words)) {
        case 1:
            return teleport_to(words[0]);
        case 2:
            return teleport_player(words[0], words[1]);
        default:
            return error_out(usage());
    }
}

string usage() {
    return "Usage: teleport [<player>] <place>";
}

int teleport_to(string place) {
    object destination =
        load_object(resolve_path(previous_object()->query_cwd(), place));

    if (!destination) {
        return error_out("Could not load object " + place);
    }

    return teleport(previous_object(), destination);
}

int teleport_player(string player, string place) {
    object *players = users();
    object destination;
    object victim;
    string name = player;
    string room = place;
    string msg = "";
    int index;
    player = lower_case(player);

    switch (lower_case(player)) {
        case "me":
        case "myself":
            name = lower_case(previous_object()->query_name());
    }
    switch (lower_case(place)) {
        case "here":
            room = file_name(here());
    }

    index = member_array(name, map(players,
                (: lower_case($1->query_name()) :)));
    if (index >= 0) {
        victim = players[index];
    }

    destination =
        load_object(resolve_path(previous_object()->query_cwd(), room));

    if (!victim) {
        msg = "Could not find player " + player;
    }
    if (!destination) {
        msg += (strlen(msg) ? "\n" : "" ) + "Could not find place " + place;
    }

    if (!msg) {
        return teleport(victim, destination);
    }

    return error_out(msg);
}

int teleport(object player, object destination) {
    return MOVE_D->move(player, destination, 1);
}
