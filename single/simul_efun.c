// mudlib: Lil
// file:   /single/simul_efun.c

#pragma show_error_context
#include <globals.h>
#include <lpctypes.h>

int same(mixed x, mixed y);
void cat(string file);
varargs int getoid(object ob);
string user_cwd(string name);
string user_path(string name);
string file_owner(string file);

string dump_variable(mixed arg);
string resolve_path(string curr, string newer);
string domain_file(string);
string creator_file(string);
string author_file(string);
void simul();

object here();

string opposite(string direction);
string unabbreviate_direction(string direction);
string abbreviate_direction(string direction);
int is_direction(string direction);

string join(string separator, string *strings);

int
same(mixed x, mixed y) {
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

void
cat(string file)
{
    write(read_file(file));
}

varargs int
getoid(object ob)
{
    int id;

    sscanf(file_name(ob || previous_object()), "%*s#%d", id);
    return id;
}

string
user_cwd(string name)
{
   return ("/u/homes/" + name[0..0] + "/" + name);
}

string user_path(string name)
{
   return (user_cwd(name) + "/");
}

// Get the owner of a file.  Used by log_error() in master.c.

string
file_owner(string file)
{
    string temp;

    if (file[0] != '/') file = "/" + file;

    if (sscanf(file, "/u/%s/%s/%*s", temp, temp) == 2) {
        return temp;
    }
    return 0;
}

// dump_variable, author: Huthar@Portals, TMI
// - returns a printable representation of any variable.
// Changed by Symmetry@IdeaExchange, Tmi-2 5/4/95
// - the format is retained
// Beek - changed to use foreach()
string
dump_variable(mixed arg)
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

string resolve_path(string curr, string newer) {
    int i, j, size;
    string *tmp;

    switch(newer) {
    case 0:
    case "":
    case ".":
	return curr;

    case "~":
	return user_path((string)this_player()->query_name());

#ifndef __NO_ENVIRONMENT__
    case "here":
	return file_name(environment())+".c";
#endif

    default:
	if (newer[0..1] == "~/") {

	    newer = user_path((string)this_player()->query_name())
		+ newer[2..];

	} else {

	    switch(newer[0]) {
	    case '~': {
		i = strsrch(newer, '/');
		if (i < 0) {
		    newer = user_path(newer[1..]);
		} else {
		    newer = user_path(newer[1..i-1]) + newer[i..];
		}

		break;
	    }

	    case '/':
		break;

	    default:
		newer = curr + "/" + newer;
	    }
    }

    if (newer[<1] != '/') {
	newer += "/";
    }

    size = sizeof(tmp = regexp(explode(newer, "/"), "."));

    i = j = 0;

    while (i < size) {
        switch(tmp[i]) {
        case "..":
	    if (j) {
		while (j-- && !tmp[j]);

		if (j >= 0)
		    tmp[j] = 0;
		else
		    j++;
	    }

        case ".":
	    tmp[i++] = 0;
	    break;

        default:
	    j = ++i;
	    break;
        }
    }
    return "/" + implode(tmp, "/");
    }
}


// domain_file should return the domain associated with a given file.

string
domain_file(string)
{
    return ROOT_UID;
}

// creator_file should return the name of the creator of a specific file.

string
creator_file(string)
{
    return ROOT_UID;
}

// author_file should return the name of the author of a specific file.

string
author_file(string)
{
    return ROOT_UID;
}

void simul() {}

object here() {
    return environment(this_player());
}

#include "directions.c"

string join(string separator, string *strings) {
    int len;
    string r = "";
    int i;

    if (strings && sizeof(strings)) {
	r += strings[0];
	len = sizeof(strings);
	if (len > 1) {
	    for (i = 1; i < len; i++) {
		r += separator + strings[i];
	    }
	}
    }
    return r;
}
