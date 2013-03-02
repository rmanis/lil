#include <globals.h>

int main(string directory) {

    string path = resolve_path(this_player()->query_cwd(), directory);
    mixed *files = stat(path);

    if (files && sizeof(files)) {
	this_player()->set_cwd(path);
    } else {
	previous_object()->tell(sprintf("%s (%s) does not exist.\n", directory, path ));
    }
}
