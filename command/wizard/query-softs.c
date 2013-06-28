
#include <globals.h>

int main(string arg) {
    previous_object()->tell(sprintf("%O\n",
                keys(here()->query_soft_objects())));
    return 1;
}
