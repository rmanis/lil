
// With influence from lima

#include <globals.h>

varargs void add_rules(string *rules, string *synonyms);

string verb = basename(file_name());

varargs void add_rules(string *rules, string *synonyms) {
    foreach (string r in rules) {
        parse_add_rule(verb, r);
        if (synonyms) {
            foreach (string s in synonyms) {
                parse_add_synonym(s, verb, r);
            }
        }
    }
}
