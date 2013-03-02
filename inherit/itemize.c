
string itemize(string *strings);

string itemize(string *strings) {
    int count = sizeof(strings);
    switch (count) {
        case 0:
            return "";
        case 1:
            return strings[0];
        case 2:
            return strings[0] + " and " + strings[1];
        default:
            return implode(strings[0..<2], ", ") + ", and " + strings[<1];
    }
}
