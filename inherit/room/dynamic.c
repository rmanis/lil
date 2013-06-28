
#include <globals.h>

int save_to_room();
void add_dynamic_comment(object editor, int start, int end);

int find_start(object editor);
int find_end(object editor);

int save_to_room() {
    string file = file_name() + ".c";
    object editor = new(EDITOR_OB, file);
    int dynamic_start;
    int dynamic_end;

    dynamic_start = find_start(editor);
    if (!dynamic_start) {
        dynamic_start = editor->length();
        editor->append(dynamic_start, "\n/* DYNAMIC START\n\n// DYNAMIC END */");
        dynamic_start = find_start(editor);
    }
    dynamic_end = find_end(editor);
    if (!dynamic_end) {
        dynamic_end = editor->length();
        editor->append(dynamic_end, "\n// DYNAMIC END */");
        dynamic_end = find_end(editor);
    }

    if (dynamic_end <= dynamic_start+1) {
        editor->insert(dynamic_end, "");
        dynamic_end++;
    }

    add_dynamic_comment(editor, dynamic_start, dynamic_end);

    editor->save();

    destruct(editor);
    return 1;
}

void add_dynamic_comment(object editor, int start, int end) {
    mapping exits = this_object()->get_exits();
    string glance = this_object()->get_glance();
    string desc = this_object()->get_description();
    mapping soft_objects = this_object()->query_soft_objects();

    // 72 for an indent of 4, a paren, and some buffer
    string rep = sprintf(
            "set_exits(%O);\n"
            "set_glance(%s);\n"
            "set_description(%s);\n"
            "set_soft_objects(%O);\n",
            exits,
            codebreak_string(glance, 72 - strlen("set_glance")),
            codebreak_string(desc, 72 - strlen("set_description")),
            soft_objects);
    string *newlines = explode(rep, "\n");
    string line;
    int i;
    for (i = 0; i < sizeof(newlines); i++) {
        line = newlines[i];

        if (regexp(line, "\\*/")) {
            line = replace_string(line, "*/", "//");
            newlines[i] = line;
        }
        if (regexp(line, "/\\*")) {
            line = replace_string(line, "/*", "//");
            newlines[i] = line;
        }
    }
    editor->change_range(start+1, end-1, implode(newlines, "\n"));
}

int find_start(object editor) {
    return editor->find_line_matching("DYNAMIC START");
}

int find_end(object editor) {
    return editor->find_line_matching("DYNAMIC END");
}
