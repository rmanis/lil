
#include <globals.h>

varargs string format(string fmt, mixed args...);
varargs void output(string fmt, mixed args...);

// Formats a string.  Does color and fill-paragraph.
varargs string format(string fmt, mixed args...) {
    string new_fmt;
    string new_str;
    object player = this_player();

    new_fmt = replace_string(fmt, "%^", "%%^");
    new_str = sprintf(new_fmt, args...);

    if (this_player()->is_logged_in()) {
        return terminal_colour(new_str, player->get_color_map(), player->get_print_width(), 0);
    }
    return terminal_colour(new_str, COLOR_OB->get_color_map(), 80, 0);
}

varargs void output(string fmt, mixed args...) {
    string str = format(fmt, args...);
    write(str);
}
