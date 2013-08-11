
#include <globals.h>

inherit "/inherit/error_out";
inherit "/inherit/tablefy";

int main(string dir);
int display_all(mixed *files);
string *fetch(string file);
int width(mixed f);
mixed *display(mixed f);

int main(string dir) {
    string path = resolve_path(this_player()->query_cwd(), dir);
    string *files;
    string *fulls;
    mixed *combined;

    if (!sizeof(stat(path))) {
	return error_out(sprintf("No such file or directory: %s", path));
    }

    if (dirp(path) && path != "/") {
	path += "/";
    }

    files = filter(get_dir(path), (: $1[0] != '.' :));

    if (filep(path)) {
        fulls = ({ path });
    } else {
        fulls = map(files, (: $(path) + $1 :));
    }

    combined = select_many(fulls, (: fetch :), path);

    return display_all(combined);
}

int display_all(mixed *files) {
    mixed *detailed = map(files, (: display :));
    string text = "";

    text = tablefy(detailed, 0, (: width :));

    print_table(text);
    return 1;
}

string *fetch(string file) {
    string obname;
    if (filep(file)) {
        obname = dirname(file) + "/" + basename(file, ".c");
        return ({ basename(file) }) + children(obname);
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
        } else if (f[<2..] == ".c") {
            return ({ color_surround("cyan", f), width(f) });
        } else if (f[<2..] == ".o") {
            return ({ color_surround("orange", f), width(f) });
        } else {
            return ({ f, width(f) });
        }
    } else if (objectp(f)) {
        return ({ color_surround("yellow", basename(sprintf("%O", f))),
                width(f) });
    }
}

