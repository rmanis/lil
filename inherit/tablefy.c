
#include <globals.h>

void print_table(string table);
varargs string tablefy(mixed *detailed, int numcols);
int select_greatest(int *nums);
int width(mixed f);

void print_table(string table) {
    write(terminal_colour(table + "\n", this_user()->query_color_map()));
}

// detailed: list of things to tablefy,
//   each element being of the form ({ string text, int width })
//   text can have pinkfish-style colors in it
//   width is the print width of text
// numcols: the number of columns of things
//
varargs string tablefy(mixed *detailed, int numcols) {
    string text = "";
    int widest;
    int i;
    int column;
    int num_spaces;

    if (!sizeof(detailed)) {
        return "";
    }

    widest = 2 + select_greatest(map(detailed, (: $1[1] :)));

    if (!numcols) {
        numcols = this_player()->query_print_width() / widest;
    }

    for (i = 0; i < sizeof(detailed); i++) {
        column = i % numcols;
        if (i && column == 0) {
            text += "\n";
        }
        num_spaces = (column < (numcols - 1) ?
                widest - detailed[i][1] :
                0);
        text +=
            sprintf("%s%s",
                detailed[i][0],
                repeat_string(" ", num_spaces));
    }
    return text;
}

int select_greatest(int *nums) {
    int n;
    int max;
    foreach (n in nums) {
        if (n > max) {
            max = n;
        }
    }
    return max;
}

int width(mixed f) {
    return stringp(f) ? strlen(f) : strlen(sprintf("%O", f));
}
