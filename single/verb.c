
#include <globals.h>

// The verb daemon

string *verbs;

void reload_verb(string file);
string *query_verbs();

void create() {
    string *files = get_dir(VERB_DIR "/*.c");
    verbs = ({ });
    if (sizeof(files)) {
        foreach (string file in files) {
            reload_verb(file);
        }
    }
}

void reload_verb(string file) {
    object o;
    string path = VERB_DIR "/" + file;
    mixed err;
    if (o = find_object(path)) {
        destruct(o);
    }

    err = catch (o = load_object(path));
    if (err) {
        write(err + "\n");
    }
    if (member_array(file, verbs) < 0) {
        verbs += ({ file });
    }
}

string *query_verbs() {
    return verbs;
}
