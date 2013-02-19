#include <globals.h>

int
main(string file)
{
    string path = resolve_path(this_player()->query_cwd(), file);
    mixed *files = stat(path);

    if (files && sizeof(files)) {
	rm(file);
    } else {
	output("%s (%s) does not exist.\n", file, path);
    }
    return 1;
}
