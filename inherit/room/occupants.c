
object *get_players();
object *get_items();

object *get_players() {
    return filter(all_inventory(this_object()), (: interactive($1) :));
}

object *get_items() {
    return filter(all_inventory(this_object()), (: !interactive($1) :));
}
