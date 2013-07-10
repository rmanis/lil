
#include <globals.h>

int main(string file) {

    string path = resolve_path(this_player()->query_cwd(), file);
    mixed *files = stat(path);

    if (files && sizeof(files) || (!dirp(path) && dirp(dirname(path)))) {
#ifdef __OLD_ED__
	ed(file);
#else
	ED_HANDLER->start_ed(path);
#endif
    } else {
	write(file + " (" + path + ") does not exist.\n");
    }
    return 1;
}
