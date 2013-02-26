
#include <globals.h>

varargs string format(string fmt, mixed args...);
varargs void output(string fmt, mixed args...);
varargs string c_format(int indent, string fmt, mixed args...);
varargs string wc_format(int width, int indent, mapping colors, string fmt, mixed args...);
varargs void c_output(int indent, string fmt, mixed args...);
string color_surround(string color, string str);

varargs string format(string fmt, mixed args...) {
    return c_format(0, fmt, args...);
}
varargs void output(string fmt, mixed args...) {
    return c_output(0, fmt, args...);
}

varargs string c_format(int indent, string fmt, mixed args...) {
    object player = this_player();
    mapping colors;

    colors = player->is_logged_in() ?
        player->get_color_map() :
        COLOR_OB->get_color_map();

    return wc_format(80, indent, colors, fmt, args...);
}

// Formats a string.  Does color and fill-paragraph.
varargs string wc_format(int width, int indent, mapping colors, string fmt, mixed args...) {
    string new_fmt;
    string new_str;

    new_fmt = replace_string(fmt, "%^", "%%^");
    new_str = sprintf(new_fmt, args...);

    return terminal_colour(new_str, colors, width, indent);
}

varargs void c_output(int indent, string fmt, mixed args...) {
    string str = c_format(indent, fmt, args...);
    write(str);
}

string color_surround(string color, string str) {
    return sprintf("%%^%s%%^%s%%^RESET%%^", upper_case(color), str);
}
