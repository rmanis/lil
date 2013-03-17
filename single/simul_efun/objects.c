#include <globals.h>
#include <lpctypes.h>

int same(mixed x, mixed y);
varargs int getoid(object ob);
string dump_variable(mixed arg);
void p_refresh();

int same(mixed x, mixed y) {
    if (typeof(x) != typeof(y)) return 0;
    switch (typeof(x)) {
        case INT:
        case STRING:
        case OBJECT:
        case FLOAT:
            return x == y;
        case MAPPING:
            if (x == y) return 1; // speed up this case
            if (sizeof(x) != sizeof(y)) return 0;
            if (!same(keys(x), keys(y))) return 0;
            if (!same(values(x), values(y))) return 0;
            return 1;
        case ARRAY:
            if (x == y) return 1; // speed up this case
            if (sizeof(x) != sizeof(y)) return 0;
            for (int i = 0; i < sizeof(x); i++) {
                if (!same(x[i], y[i])) return 0;
            }
            return 1;
        case BUFFER:
        case FUNCTION:
        case CLASS:
            error("Not implemented.");
    }
}

varargs int getoid(object ob)
{
    int id;

    sscanf(file_name(ob || previous_object()), "%*s#%d", id);
    return id;
}

// dump_variable, author: Huthar@Portals, TMI
// - returns a printable representation of any variable.
// Changed by Symmetry@IdeaExchange, Tmi-2 5/4/95
// - the format is retained
// Beek - changed to use foreach()
string dump_variable(mixed arg)
{
    string rtn;
    mixed x, y;

    switch(typeof(arg)) {
        case OBJECT: return "("+file_name(arg)+")";
        case STRING: return "\""+arg+"\"";
        case INT: return "#"+arg;
        case ARRAY:
        {
            rtn = "ARRAY\n";
            foreach (y in arg)
                rtn += sprintf("[%d] == %s\n", x++, dump_variable(y));

            return rtn;
        }

        case MAPPING:
        {
            rtn = "MAPPING\n" +
            implode(values(map_mapping(arg,
                            (: sprintf("[%s] == %s", $1, $2) :))), "\n");
            return rtn;
        }

        case FUNCTION:
        case CLASS:
        case FLOAT:
        case BUFFER:
        {
            return sprintf("%O\n", arg);
        }

        return "UNKNOWN";
    }
}

// Force the master to refresh parsing stuff.
void p_refresh() {
    "/single/master"->p_refresh();
}
