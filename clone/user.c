// mudlib:   Lil 
// file:     user.c
// purpose:  is the representation of an interactive (user) in the MUD

#include <globals.h>

inherit BASE;
inherit COMMAND_OB;
inherit __DIR__ "user/terminal";

private string old_input = "";
private string name;
private string cwd = "/";
private string room;

private static int logged_in;

string save_filename();
void save();
void manual_save();
void disable_autosave();
void autosave(int save_now);
void load();
void quit();

string query_cwd();
string query_name();
string get_room();
void set_room(string filename);
void set_name(string arg);
int is_logged_in();
varargs void tell(string str, int indent);

void move(mixed location);

#ifdef __INTERACTIVE_CATCH_TELL__
void catch_tell(string str) {
    receive(str);
}
#endif

string save_filename() {
    return sprintf("/data/user/%s", query_name());
}

void save() {
    string savefile = save_filename();

    ensure_path_of_file_exists(savefile);

    if (save_object(savefile)) {
        tell("%^BOLD%^%^GREEN%^Saved.%^RESET%^\n");
    } else {
        tell("%^BOLD%^%^RED%^Error saving file.%^RESET%^\n");
    }
}

void manual_save() {
    int callout = remove_call_out("autosave");
    save();
    if (callout >= 0) {
        autosave(0);
    }
}

void disable_autosave() {
    remove_call_out("autosave");
}

void autosave(int save_now) {
    if (save_now) {
        tell("%^CYAN%^Autosaving...%^RESET%^\n");
        save();
    }
    call_out("autosave", SAVE_PERIOD, 1);
}

void load() {
    string fname = save_filename();
    if (sizeof(stat(fname + ".o"))) {
        restore_object(fname);
    }
}

void quit() {
    save();
    shout(color_surround("bold",
                sprintf("[ %s leaves the mud ]\n", query_name())));
}

string get_room() {
    if (!room) {
        room = START_ROOM;
    }
    return room;
}

void set_room(string filename) {
    room = filename;
}

string
query_cwd()
{
    if (!cwd) {
        cwd = "/";
    }
    return cwd;
}

void set_cwd(string newcwd) {
    cwd = newcwd;
}

// query_name: called by various objects needing to know this user's name.
string
query_name()
{
    return name;
}

void
set_name(string arg)
{
//  may wish to add security to prevent just anyone from changing
//  someone else's name.
    name = arg;
}

int is_logged_in() {
    return logged_in;
}

// called by the present() efun (and some others) to determine whether
// an object is referred as an 'arg'.

int
id(string arg)
{
    return (arg == query_name()) || base::id(arg);
}

#ifndef __OLD_ED__
void
write_prompt() {
    switch (query_ed_mode()) {
    case 0:
    case -2:
        tell(":");
        break;

    case -1:
        tell("%^RESET%^> ");
        break;

    default:
        tell("*\b");
        break;
    }
}

void
start_ed(string file) {
    tell(ed_start(file, 0));
}
#endif

varargs void tell(string str, int indent) {
    if (indent) {
        tell_object(this_object(), format(indent, "%s", str));
    } else {
        tell_object(this_object(), format(0, "%s", str));
    }
}

void move(mixed location) {
    ::move(location);

    if (objectp(location)) {
        set_room(file_name(location));
    } else if (stringp(location)) {
        set_room(location);
    }

    LOOK_D->player_glance(this_object());
}

#ifdef __NO_ADD_ACTION__
void process_input(string arg) {
    mixed pre;

#ifndef __OLD_ED__
    if (query_ed_mode() != -1) {
    if (arg[0] != '!') {
        tell(ed_cmd(arg));
        return;
    }
    arg = arg[1..];
    }
#endif
    if (arg == "!") {
        arg = old_input;
    } else {
        old_input = arg;
    }

    pre = get_prefix(arg[0]);
    if (pre) {
        arg = pre + " " + arg[1..];
    }
    if (trim(arg) == "stop") {
        clear_queue();
    } else {
        try_execute(arg);
    }
}
#else
string
process_input(string arg)
{
#ifndef __OLD_ED__
    if (query_ed_mode() != -1) {
    if (arg[0] != '!') {
        tell(ed_cmd(arg));
        return 0;
    }
    arg = arg[1..];
    }
#endif
    // possible to modify player input here before driver parses it.
    return arg;
}

int
commandHook(string arg)
{
    string cmd_path;
    object cobj;

    cmd_path = COMMAND_PREFIX + query_verb();

    cobj = load_object(cmd_path);
    if (cobj) {
    return (int)cobj->main(arg);
    } else {
    // maybe call an emote/soul daemon here
    }
    return 0;
}

// init: called by the driver to give the object a chance to add some
// actions (see the MudOS "applies" documentation for a better description).

void
init()
{
    // using "" as the second argument to add_action() causes the driver
    // to call commandHook() for those user inputs not matched by other
    // add_action defined commands (thus 'commandHook' becomes the default
    // action for those verbs without an explicitly associated action).
    if (this_object() == this_player()) {
        add_action("commandHook", "", 1);
    }
}
#endif

// create: called by the driver after an object is compiled.

void
create()
{
#ifdef __PACKAGE_UIDS__
    seteuid(0); // so that login.c can export uid to us
#endif
}

// receive_message: called by the message() efun.

void
receive_message(string newclass, string msg)
{
    // the meaning of 'class' is at the mudlib's discretion
    receive(msg);
}

int move_or_destruct(object ob) {
    tell("You feel the world crumble around you.\n");
    MOVE_D->move(this_object(), VOID_OB, 1);
    return 0;
}

// setup: used to configure attributes that aren't known by this_object()
// at create() time such as living_name (and so can't be done in create()).

void
setup()
{
    set_heart_beat(1);
#ifdef __PACKAGE_UIDS__
    seteuid(getuid(this_object()));
#endif
#ifndef __NO_WIZARDS__
    enable_wizard();
#endif
#ifndef __NO_ADD_ACTION__
    set_living_name(query_name());
    enable_commands();
    add_action("commandHook", "", 1);
#else
    set_this_player(this_object());
#endif
    load();
    autosave(0);

    logged_in = 1;
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.

#ifndef __NO_ENVIRONMENT__
void tell_room(object ob, string msg) {
    foreach (ob in all_inventory(ob) - ({ this_object() }))
        tell_object(ob, msg);
}
#endif

void
net_dead()
{
    set_heart_beat(0);
#ifndef __NO_ENVIRONMENT__
    tell_room(environment(), query_name() + " is link-dead.\n");
#endif
}

// reconnect: called by the login.c object when a netdead player reconnects.

void
reconnect()
{
    set_heart_beat(1);
#ifndef __NO_ENVIRONMENT__
    tell_room(environment(), "Reconnected.\n");
    tell_room(environment(), query_name() + " has reconnected.\n");
#endif
}
