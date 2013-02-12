#include <globals.h>

int
main(string file)
{
    object obj;
    string path;

    if (!file) {
#ifndef __NO_ADD_ACTION__
	return notify_fail("update what?\n");
#else
	write("update what?\n");
	return 1;
#endif
    }

    path = resolve_path(this_player()->query_cwd(), file);

    if (!sizeof(stat(path)) && !sizeof(stat(path + ".c"))) {
	write(file + " (" + path + ") does not exist.\n");
    }

    if (obj = find_object(path)) {
	destruct(obj);
    }
    load_object(path);
    return 1;
}
