
#include <globals.h>

void create(string *paths);
string *read(string path);
void start();
void prompt();
void handle(string arg);

void print_page();
void help();
void next_book();
void previous_book();
void next_page();
void previous_page();

string *filenames = ({ });
mixed *books;
int current_book = 0;
int current_line = 0;

// TODO: Pull parts of this and parts of editor to common ancestor.
// TODO: Don't restrict to just files.
void create(string *paths) {
    filenames = paths;
}

string *read(string path) {
    string contents = read_file(path);
    return explode(contents, "\n");
}

void start() {
    books = map(filenames, (: read :));
    this_player()->push_handler((: handle :), (: prompt :));
    print_page();
}

void prompt() {
    write(":");
}

// TODO: handle search forwards and backwards
void handle(string arg) {
    string trimmed = trim(arg);
    switch (trimmed) {
        case "h":
            help();
            break;
        case "<":
            previous_book();
            break;
        case ">":
            next_book();
            break;
        case "":
            next_page();
            break;
        case "b":
            previous_page();
            break;
        case "q":
            this_player()->pop_handler();
            break;
    }
}

void print_page() {
    string *book = books[current_book];
    int length = this_player()->query_print_height() - 2;
    int start = current_line;
    int end = start + length;
    string page;

    if (end >= sizeof(book)) {
        end = sizeof(book) - 1;
    }

    page = implode(book[start..end], "\n") + "\n";
    write(page);
}

void help() {
    mixed *lines = ({
            ({ "space - ", "Page down" }),
            ({ "b - ", "Page up" }),
            ({ "< - ", "Previous file" }),
            ({ "> - ", "Next file" }),
            ({ "q - ", "quit" }),
            });
    string *line;

    foreach (line in lines) {
        this_player()->tell(line[0] + line[1] + "\n", strlen(line[0]));
    }
}

void next_book() {
    if (current_book < sizeof(books) - 1) {
        current_book++;
        current_line = 0;
        print_page();
    } else {
        this_player()->tell("Can't go to next!\n");
    }
}

void previous_book() {
    if (current_book > 0) {
        current_book--;
        current_line = 0;
        print_page();
    } else {
        this_player()->tell("Can't go to previous!\n");
    }
}

void next_page() {
    int amount = this_player()->query_print_height() - 2;
    int new_line = current_line + amount;
    if (new_line >= sizeof(books[current_book])) {
        this_player()->tell("End of file.\n");
    } else {
        current_line = new_line;
        print_page();
    }
}

void previous_page() {
    int amount = this_player()->query_print_height() - 2;
    int new_line = current_line - amount;
    if (current_line == 0) {
        this_player()->tell("Beginning of file.\n");
    } else {
        if (new_line < 0) {
            current_line = 0;
        } else {
            current_line = new_line;
        }
        print_page();
    }
}
