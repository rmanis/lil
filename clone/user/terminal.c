
#include <colors.h>

mapping new_color_map();
int get_print_width();
int get_print_height();

private mapping colors;

private int print_width;
private int print_height;

int get_print_width() {
    if (!print_width) {
        print_width = 80;
    }
    return print_width;
}

int get_print_height() {
    if (!print_height) {
        print_height = 24;
    }
    return print_height;
}

mapping get_color_map() {
    if (!colors) {
        colors = new_color_map();
    }
    return colors;
}

mapping new_color_map() {
    return ([ "RESET" : RESET,
            "BOLD" : BOLD,
            "FLASH" : FLASH,
            "BLACK" : BLACK,
            "RED" : RED,
            "GREEN" : GREEN,
            "ORANGE" : ORANGE,
            "YELLOW" : YELLOW,
            "BLUE" : BLUE,
            "CYAN" : CYAN,
            "MAGENTA" : MAGENTA,
            "WHITE" : WHITE,
            "B_RED" : B_RED,
            "B_GREEN" : B_GREEN,
            "B_ORANGE" : B_ORANGE,
            "B_YELLOW" : B_YELLOW,
            "B_BLUE" : B_BLUE,
            "B_CYAN" : B_CYAN,
            "B_BLACK" : B_BLACK,
            "B_WHITE" : B_WHITE,
            "CLEARLINE" : CLEARLINE,
            "B_MAGENTA" : B_MAGENTA,
            "INITTERM" : INITTERM,
            "ENDTERM" : ENDTERM,
            "SAVE" : SAVE,
            "RESTORE" : RESTORE,
            "HOME" : HOME ]);
}
