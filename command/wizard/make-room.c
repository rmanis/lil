
#include <globals.h>

inherit "/inherit/error_out";

int main(string args) {
    string trimmed = trim(args);
    int ispace = member_array(' ', trimmed);
    string search = "set_description(";
    string filename;
    string localname;
    string description;
    string brief;
    int start;
    int end;
    string contents;
    string new_contents;

    if (!strlen(trimmed)) {
        return error_out("Usage: make-room <file> [ <description> ]");
    }

    if (ispace > 0) {
        description = trimmed[ispace+1..];
        localname = trimmed[0..ispace-1];
    } else {
        localname = trimmed;
    }

    filename = resolve_path(this_player()->query_cwd(), localname);

    if (load_object(filename)) {
        return error_out(sprintf("File %s.c already exists.", filename));
    }

    filename += ".c";

    contents = read_file(ROOM_TEMPLATE);
    brief = basename(localname);
    contents = replace_string(contents, "GLANCE", sprintf("%O", brief));

    if (strlen(description)) {
        start = strsrch(contents, search) + strlen(search);
        end = strsrch(contents[start+1..], '"') + start + 1;

        start--;
        end++;

        new_contents = contents[0..start] +
            sprintf("%O", description) +
            contents[end..];
    } else {
        new_contents = contents;
    }

    return write_file(filename, new_contents, 1);
}
