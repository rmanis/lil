
#include <globals.h>

void handle_ed(string arg);
void start_ed(string file);
void prompt_ed();

void handle_ed(string arg) {
#ifndef __OLD_ED__
    if (query_ed_mode() != -1) {
        if (arg[0] == '!') {
            evaluate(this_player()->previous_handler(), arg[1..]);
        } else {
            write(ed_cmd(arg));
        }
    } else {
        this_player()->pop_handler();
        evaluate(this_player()->query_handler(), arg);
    }
#endif
}

void start_ed(string file) {
    this_player()->push_handler((: handle_ed :), (: prompt_ed :));
    write(ed_start(file, 0));
}

void prompt_ed() {
    switch (query_ed_mode()) {
    case 0:
    case -2:
        write(":");
        break;

    case -1:
        evaluate(this_player()->previous_prompt());
        break;

    default:
        write("*\b");
        break;
    }
}
