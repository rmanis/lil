
#include <globals.h>

// Editor.  Supports searching, replacing, insertion, appending, deleting,
// saving.
//
// The first line is line 1.

string *lines;
string filename;

void create(string file);
varargs void save(string filename);
string *query_lines();
varargs int find_line_matching(string pattern, int start);
void insert(int insertion_point, string text);
void append(int after, string text);
void delete_line(int line);
void delete_lines(int start, int end);
string get_line(int num);
void change_line(int num, string replacement);
void change_range(int start, int end, string replacement);
int length();

void create(string file) {
    string contents;

    filename = file;

    if (filep(file)) {
        contents = read_file(file);
        lines = explode(contents, "\n");
    } else {
        lines = ({ "" });
    }
}

varargs void save(string file) {
    if (file) {
        filename = file;
    }

    write_file(filename, implode(lines, "\n") + "\n", 1);
}

string *query_lines() {
    return lines;
}

varargs int find_line_matching(string pattern, int start) {
    string line;
    int index = 1;
    if (start) {
        start--;
    }

    foreach (line in lines[start..]) {
        if (regexp(line, pattern)) {
            return index + start;
        }
        index++;
    }

    return 0;
}

void insert(int insertion_point, string text) {
    string *news = explode(text, "\n");
    insertion_point--;
    if (insertion_point == 0) {
        lines = news + lines;
    } else {
        lines = lines[0..insertion_point-1] +
            news +
            lines[insertion_point..];
    }
}

void append(int after, string text) {
    insert(after + 1, text);
}

void delete_line(int line) {
    delete_lines(line, line);
}

void delete_lines(int start, int end) {
    start--;
    end--;
    lines = lines[0..start-1] + lines[end+1..];
}

string get_line(int num) {
    num--;
    return lines[num];
}

void change_line(int num, string replacement) {
    change_range(num, num, replacement);
}

void change_range(int start, int end, string replacement) {
    string *replace;
    start--;
    end--;
    replace = explode(replacement, "\n");

    lines = lines[0..start-1] +
        replace +
        lines[end+1..];
}

int length() {
    return sizeof(lines);
}
