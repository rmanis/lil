
#include <globals.h>

inherit "/inherit/error_out";

string *fetch(string file) {
    if (filep(file)) {
        return ({ basename(file) }) + children(file);
    } else {
        return ({ basename(file) + "/" });
    }
}

int width(mixed f) {
    if (stringp(f)) {
        return strlen(f);
    } else if (objectp(f)) {
        return strlen(basename(sprintf("%O", f)));
    }
}

mixed *display(mixed f) {
    if (stringp(f)) {
        if (f[<1] == '/') {
            return ({ color_surround("green", f), width(f) });
        } else {
            return ({ color_surround("cyan", f), width(f) });
        }
    } else if (objectp(f)) {
        return ({ color_surround("yellow", basename(sprintf("%O", f))),
                width(f) });
    }
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

int display_all(mixed *files, int screen_width) {
    int widest;
    int numcols;
    mixed *detailed = map(files, (: display :));
    int i;
    int column;
    int num_spaces;
    string text = "";

    widest = select_greatest(map(files, (: width :)));

    numcols = screen_width / widest;

    for (i = 0; i < sizeof(detailed); i++) {
        column = i % numcols;
        if (i && column == 0) {
            text += "\n";
        }
        num_spaces = (column < (numcols - 1) ?
                1 + widest - detailed[i][1] :
                0);
        text +=
            sprintf("%s%s",
                detailed[i][0],
                repeat_string(" ", num_spaces));
    }
    write(terminal_colour(text + "\n", this_user()->query_color_map()));
    return 1;
}

int main(string dir) {
    string path = resolve_path(this_player()->query_cwd(), dir);
    string *files;
    string *fulls;
    mixed *combined;
    int screen_width = this_player()->query_print_width();

    if (!sizeof(stat(path))) {
	return error_out(sprintf("No such file or directory: %s", path));
    }

    if (stringp(stat(path)[0]) && path != "/") {
	path += "/";
    }

    files = filter(get_dir(path), (: $1[0] != '.' :));

    fulls = map(files, (: $2 + $1 :), path);
    combined = select_many(fulls, (: fetch :), path);

    return display_all(combined, screen_width);
}
