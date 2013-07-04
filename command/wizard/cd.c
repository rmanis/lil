
#include <globals.h>

int main(string directory) {

    string trimmed = trim(directory);
    string path;
    mixed *files;

    if (strlen(trimmed)) {
        path = resolve_path(this_player()->query_cwd(), trimmed);
        files = stat(path);
        if (files && sizeof(files)) {
            this_player()->set_cwd(path);
        } else {
            this_player()->tell(sprintf("%s (%s) does not exist.\n", trimmed, path ));
        }
    } else {
        path = user_cwd(this_player()->query_name());
        this_player()->set_cwd(path);
    }
}
