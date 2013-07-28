
#include <globals.h>

inherit "/inherit/command/multi-file";

string *paths = ({ });

string usage() {
    return "Usage: more { <file> }";
}

void operate(string path) {
    paths += ({ path });
}

void pre_op(string *paths) {
    paths = ({ });
}

int post_op() {
    object pager = new(PAGER_OB, paths);

    pager->start();
    return 1;
}
