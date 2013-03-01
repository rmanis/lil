
int whitespace(int char) {
    return char == ' ' || char == '\t' || char == '\n';
}

string trim(string str) {
    string sub = "";
    int i;
    int j;
    int len;

    if (!str || !strlen(str)) {
        return "";
    }

    len = strlen(str);
    for (i = 0; (i < len) && whitespace(str[i]); i++);
    for (j = len - 1; (j >= 0) && whitespace(str[j]); j--);

    if (i < len && j >= 0) {
        sub = str[i..j];
    }
    return sub;
}
