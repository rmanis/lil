
#include <globals.h>

void handle_ed(string arg);
void start_ed(string file);
void prompt_ed();

// prototypes from elsewhere
function query_handler();
function previous_handler();
void push_handler(function handler);
void pop_handler();
function query_prompt();
function previous_prompt();
void push_prompt(function prompt);
void pop_prompt();

void handle_ed(string arg) {
#ifndef __OLD_ED__
    if (query_ed_mode() != -1) {
        if (arg[0] == '!') {
            evaluate(previous_handler(), arg[1..]);
        } else {
            write(ed_cmd(arg));
        }
    } else {
        pop_prompt();
        pop_handler();
        evaluate(query_handler(), arg);
    }
#endif
}

void start_ed(string file) {
    push_prompt( (: prompt_ed :) );
    push_handler( (: handle_ed :) );
    write(ed_start(file, 0));
}

void prompt_ed() {
    switch (query_ed_mode()) {
    case 0:
    case -2:
        write(":");
        break;

    case -1:
        evaluate(previous_prompt());
        break;

    default:
        write("*\b");
        break;
    }
}
