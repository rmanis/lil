
#include <globals.h>

inherit "/inherit/error_out";

int
main(string file)
{
    object obj;
    string path;

    if (!file) {
        return error_out("update what?");
    }

    path = resolve_path(this_player()->query_cwd(), file);

    if (!sizeof(stat(path)) && !sizeof(stat(path + ".c"))) {
	output(file + " (" + path + ") does not exist.\n");
    }

    if (obj = find_object(path)) {
	destruct(obj);
    }
    load_object(path);
    return 1;
}
