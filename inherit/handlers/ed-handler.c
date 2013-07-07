
#include <globals.h>

void handle_ed(string arg);

// prototypes from elsewhere
varargs void tell(string str, int indent);
function query_handler();
function previous_handler();
void push_handler(function handler);
void pop_handler();

void handle_ed(string arg) {
#ifndef __OLD_ED__
    if (query_ed_mode() != -1) {
        if (arg[0] == '!') {
            evaluate(previous_handler(), arg[1..]);
        }
        this_object()->tell(ed_cmd(arg));
    } else {
        pop_handler();
        evaluate(query_handler(), arg);
    }
#endif
}

void start_ed(string file) {
    push_handler( (: handle_ed :) );
    tell(ed_start(file, 0));
}
