
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

void set_print_width(int w) {
    print_width = w;
}

void set_print_height(int h) {
    print_height = h;
}

int get_print_height() {
    if (!print_height) {
        print_height = 24;
    }
    return print_height;
}

void window_size(int width, int height) {
    set_print_width(width);
    set_print_height(height);
    output("New window size: %d x %d", width, height);
}
