#include <globals.h>

int main(string directory) {

    string path = resolve_path(this_player()->query_cwd(), directory);
    mixed *files = stat(path);

    if (files && sizeof(files)) {
	this_player()->set_cwd(path);
    } else {
	write(directory + " (" + path + ") does not exist.\n");
    }
}
