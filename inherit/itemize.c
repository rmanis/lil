string itemize(object *objects) {
    string *names;
    int count;

    if (objects) {
        count = sizeof(objects);
        names = map(objects, (: $1->query_name() :));

        switch (count) {
            case 0:
                return "";
            case 1:
                return names[0];
            case 2:
                return names[0] + " and " + names[1];
            default:
                return implode(names[0..<2], ", ") + ", and " + names[count-1];
        }
    }
}
