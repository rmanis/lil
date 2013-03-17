
#include <globals.h>

varargs void shout(string str, object shouter);
varargs void tell_room(mixed room, string str, object *exclude, int indent);
varargs string wc_format(int width, int indent, mapping colors, string fmt, mixed args...);
string color_surround(string color, string str);

varargs void shout(string str, object shouter) {
    object p;
    foreach (p in users()) {
        if (p != shouter) {
            p->tell(str);
        }
    }
}

varargs void tell_room(mixed room, string str, object *exclude, int indent) {
    object o;
    if (stringp(room)) {
        room = load_object(room);
    }
    if (room) {
        foreach (o in all_inventory(room) - exclude) {
            if (inherits(USER_TERM, o)) {
                o->tell(str, indent);
            } else if (!inherits(ROOM_OB, o)) {
                tell_object(o, str);
            }
        }
    }
}

// Formats a string.  Does color and fill-paragraph.
varargs string wc_format(int width, int indent, mapping colors, string fmt, mixed args...) {
    string new_fmt;
    string new_str;

    new_fmt = replace_string(fmt, "%^", "%%^");
    new_str = sprintf(new_fmt, args...);

    return terminal_colour(new_str, colors, width, indent);
}

varargs string color_surround(string color, string arg2, string arg3) {
    string reset = "RESET";
    string msg = arg2;
    if (arg3) {
        reset = upper_case(arg2);
        msg = arg3;
    }
    return sprintf("%%^%s%%^%s%%^%s%%^", upper_case(color), msg, reset);
}
