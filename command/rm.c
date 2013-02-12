#include <globals.h>

int
main(string file)
{
    string path = resolve_path(this_player()->query_cwd(), file);
    mixed *files = stat(path);

    if (files && sizeof(files)) {
	rm(file);
    } else {
	write(file + " (" + path + ") does not exist.\n");
    }
    return 1;
}
