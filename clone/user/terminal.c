
inherit __DIR__ "color";

int get_print_width();
int get_print_height();

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

}
