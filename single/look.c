
// The look daemon.  Could take into account lighting, visibility, invisibility, &c.

inherit "/inherit/itemize";

void player_look(object player);
void player_glance(object player);

void player_look(object player) {
    object room;
    string description;
    string *directions;
    string exits;
    string players;
    string items;
    string msg;

    if (player) {
        room = environment(player);
        description = room->get_description();
        directions = room->exit_directions();
        exits = sizeof(directions) ?
            "Exits: " + itemize(directions) :
            "There are no obvious exits.";
        players = itemize(map(room->get_players() - ({ player }),
                    (: $1->query_name() :)));
        items = itemize(map(room->get_items(), (: $1->query_name() :)));

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
    string players;
    string items;
    string msg;

    if (player) {
        room = environment(player);
        description = room->get_glance();
        exits = "[" +
            implode(map(room->exit_directions(),
                        (: abbreviate_direction($1) :)),
                    ",") +
                "]";
        players = itemize(map(room->get_players() - ({ player }),
                    (: $1->query_name() :)));
        items = itemize(map(room->get_items(), (: $1->query_name() :)));

        msg = description + " " +
            color_surround("green", exits) + "\n" +
            (strlen(players) ? (players + "\n") : "") +
            (strlen(items) ? (items + "\n") : "");
        player->tell(msg);
    }
}
