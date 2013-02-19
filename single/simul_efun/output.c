
varargs string format(string fmt, mixed args...);
varargs void output(string fmt, mixed args...);

// Formats a string.  Does color and fill-paragraph.
varargs string format(string fmt, mixed args...) {
    string new_fmt;
    string new_str;

    new_fmt = replace_string(fmt, "%^", "%%^");
    new_str = sprintf(new_fmt, args...);

    return terminal_colour(new_str, this_player()->get_color_map(), this_player()->get_print_width(), 0);
}

varargs void output(string fmt, mixed args...) {
    string str = format(fmt, args...);
    write(str);
}
