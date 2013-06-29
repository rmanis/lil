
object *query_players();
object *query_items();

object *query_players() {
    return filter(all_inventory(this_object()), (: interactive($1) :));
}

object *query_items() {
    return filter(all_inventory(this_object()), (: !interactive($1) :));
}
