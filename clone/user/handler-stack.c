
#include <globals.h>

class handler {
    function input;
    function prompt;
}

static class handler *stack = ({ });

void process_command(string arg);
varargs void tell(string str, int indent);

void handle_input(string arg);
function query_handler();
function previous_handler();

function query_prompt();
function previous_prompt();

void push_handler(function input_handler, function prompt);
void pop_handler();

void handle_input(string arg) {
    function handler;
    function prompt;

    handler = query_handler();
    if (!handler) {
        handler = (: process_command :);
        prompt = (: tell("%^RESET%^> ") :);
        push_handler(handler, prompt);
    }

    evaluate(handler, arg);
}

function query_handler() {
    class handler top;

    if (sizeof(stack)) {
        top = stack[0];
        return top->input;
    }
}

function previous_handler() {
    class handler top;

    if (sizeof(stack) > 1) {
        top = stack[1];
        return top->input;
    }
}

function query_prompt() {
    class handler top;

    if (sizeof(stack)) {
        top = stack[0];
        return top->prompt;
    }
}

function previous_prompt() {
    class handler top;

    if (sizeof(stack) > 1) {
        top = stack[1];
        return top->prompt;
    }
}

void push_handler(function input_handler, function prompt) {
    class handler new_handler = new(class handler);
    new_handler->input = input_handler;
    new_handler->prompt = prompt;

    stack = ({ new_handler }) + stack;
}

void pop_handler() {
    if (sizeof(stack)) {
        stack = stack[1..];
    }
}
