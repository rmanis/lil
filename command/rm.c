
#include <globals.h>

inherit "/inherit/error_out";

int
main(string file)
{
    string path = resolve_path(this_player()->query_cwd(), file);
    mixed *files = stat(path);

    if (files && sizeof(files)) {
	rm(file);
    } else {
        return error_out(sprintf("%s (%s) does not exist.", file, path));
    }
    return 1;
}
