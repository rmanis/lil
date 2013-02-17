#include <globals.h>
#include <lpctypes.h>

string domain_file(string);
string creator_file(string);
string author_file(string);

void cat(string file);

string user_cwd(string name);
string user_path(string name);
string file_owner(string file);
string resolve_path(string curr, string newer);

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

void
cat(string file)
{
    write(read_file(file));
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

