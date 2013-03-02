#include <globals.h>

int main(string arg) {
    previous_object()->tell(sprintf("%s\n", this_player()->query_cwd()));
    return 1;
}
