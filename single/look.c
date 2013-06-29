
// The look daemon.  Could take into account lighting, visibility, invisibility, &c.

inherit "/inherit/itemize";

void player_look(object player);
void player_glance(object player);

string string_presence(string *str);

void player_look(object player) {
    object room;
    string description;
    string *directions;
    string exits;
    object *pobs;
    object *iobs;
    string players;
    string items;
    string msg;

    if (player) {
        room = environment(player);
        description = room->query_description();
        directions = room->exit_directions();

        exits = sizeof(directions) ?
            "Exits: " + itemize(directions) :
            "There are no obvious exits.";

        pobs = room->query_players() - ({ player });
        players = string_presence(map(pobs, (: $1->query_in_room_name() :)));

        iobs = room->query_items();
        items = string_presence(map(iobs, (: $1->query_in_room_name() :)));

        msg = description + "\n" +
            color_surround("green", exits + "\n") +
            (strlen(players) ? (players + "\n") : "") +
            (strlen(items) ? (items + "\n") : "");

        player->tell(msg);
    }
}

void player_glance(object player) {
    object room;
    string description;
    string exits;
    object *pobs;
    object *iobs;
    string players;
    string items;
    string msg;

    if (player) {
        room = environment(player);
        description = room->query_glance();
        exits = "[" +
            implode(map(room->exit_directions(),
                        (: abbreviate_direction($1) :)),
                    ",") + "]";

        pobs = room->query_players() - ({ player });
        iobs = room->query_items();

        players = string_presence(map(pobs, (: $1->query_in_room_name() :)));
        items = string_presence(map(iobs, (: $1->query_in_room_name() :)));

        msg = description + " " +
            (player->query_wizard() && room->query_grubby() ?
             color_surround("yellow", "*") : "") +
            color_surround("green", exits) + "\n" +
            (strlen(players) ? (players + "\n") : "") +
            (strlen(items) ? (items + "\n") : "");
        player->tell(msg);
    }
}

string string_presence(string *str) {
    int count = sizeof(str);
    return itemize(str) +
        (count == 1 ? " is here." :
         count > 1 ? " are here." :
         "");
}
