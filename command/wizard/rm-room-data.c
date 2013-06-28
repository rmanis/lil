
#include <globals.h>

inherit "/inherit/error_out";

int main(string arg) {
    string fname = here()->data_file_name() + ".o";
    if (filep(fname)) {
        rm(fname);
    } else {
        return error_out(sprintf("%s does not exist.", fname));
    }

    return 0;
}
