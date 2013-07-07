
#include <globals.h>

#define PUSH(thing,place) place = ({ thing }) + place
#define POP(place) place = place[1..]
#define PEEK(place) do { if (sizeof(place)) { return place[0]; } } while (0)
#define PREVIOUS(place) do { if (sizeof(place) > 1) { return place[1]; } } while (0)

static function *stack = ({ });
static function *prompts = ({ });

void process_command(string arg);

void handle_input(string arg);
function query_handler();
function previous_handler();
void push_handler(function handler);
void pop_handler();

function query_prompt();
function previous_prompt();
void push_prompt(function prompt);
void pop_prompt();

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
    PEEK(stack);
}

function previous_handler() {
    PREVIOUS(stack);
}

void push_handler(function handler) {
    if (handler) {
        PUSH(handler, stack);
    }
}

void pop_handler() {
    POP(stack);
}

function query_prompt() {
    PEEK(prompts);
}

function previous_prompt() {
    PREVIOUS(prompts);
}

void push_prompt(function prompt) {
    if (prompt) {
        PUSH(prompt, prompts);
    }
}

void pop_prompt() {
    POP(prompts);
}
