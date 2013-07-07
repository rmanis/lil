
#include <globals.h>

static function *stack = ({ });

void handle_input(string arg);
function query_handler();
function previous_handler();
void push_handler(function handler);
void pop_handler();
void process_command(string arg);

void handle_input(string arg) {
    function handler;

    handler = query_handler();
    if (!handler) {
        handler = (: process_command($1) :);
        push_handler(handler);
    }

    evaluate(handler, arg);
}

function query_handler() {
    if (sizeof(stack)) {
        return stack[0];
    }
}

function previous_handler() {
    if (sizeof(stack) > 1) {
        return stack[1];
    }
}

void push_handler(function handler) {
    if (handler) {
        stack = ({ handler }) + stack;
    }
}

void pop_handler() {
    stack = stack[1..];
}
