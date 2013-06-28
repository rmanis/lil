
#include <globals.h>

string quoted(string str);
int whitespace(int char);
string trim(string str);
string *split_newlines(string *words);
varargs string codebreak_string(string str, int firstlen, int restlen);

string quoted(string str) {
    return "\"" + str + "\"";
}

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

string *split_newlines(string *words) {
    string *r = ({ });
    string *subwords;
    string subword;
    string builtword = "";
    string word;

    foreach (word in words) {
        subwords = reg_assoc(word, ({ "\\\\n" }), ({ 0 }))[0];
        if (word == "") {
            // Cruft to handle double(-plus?) spaces.
            r += ({ builtword, word });
            builtword = "";
        } else {
            foreach (subword in subwords) {
                if (subword == "\\n" || subword == "") {
                    builtword += subword;
                } else {
                    if (strlen(builtword)) {
                        r += ({ builtword });
                    }
                    builtword = subword;
                }
            }
        }
    }
    r += ({ builtword });

    return r;
}

// Return a string representation of `str` broken into lines
// firstlen is the maximum length of the first line
// restlen is the maximum length of the rest of the lines
// quotation marks are included for both
varargs string codebreak_string(string str, int firstlen, int restlen) {
    string input = str;
    string *words;
    mixed *lines = ({ });
    string current_line = "";
    int i;
    int len;
    int comparator;
    int linenum = 1;
    string space;

    if (!str) {
        return 0;
    }

    if (!firstlen) {
        firstlen = 72;
    }
    if (!restlen) {
        restlen = 68;
    }
    firstlen -= 2;
    restlen -= 2;

    input = replace_string(input, "\\", "\\\\");
    input = replace_string(input, "\t", "\\t");
    input = replace_string(input, "\n", "\\n");
    input = replace_string(input, "\"", "\\\"");

    words = explode(input, " ");
    words = split_newlines(words);

    for (i = 0; i < sizeof(words); i++) {
        space = (i == (sizeof(words) - 1)) ? "" : " ";

        comparator = (linenum == 1) ? firstlen : restlen;

        if (regexp(words[i], "\\\\n$")) {
            len += strlen(words[i]);
            if (len <= comparator) {
                current_line += words[i];
                lines += ({ current_line });
            } else {
                lines += ({ current_line, words[i] });
                linenum++;
            }
            current_line = "";
            len = 0;
            linenum++;
        } else {
            len += strlen(words[i]) + strlen(space);
            if (len > comparator) {
                lines += ({ current_line });
                current_line = words[i] + space;
                len = strlen(current_line);
                linenum++;
            } else {
                current_line += words[i] + space;
            }
        }
    }

    lines += ({ current_line });

    lines = map(lines, (: sprintf("%O", $1) :));
    return implode(lines, "\n");
}
