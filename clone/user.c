// mudlib:   Lil 
// file:     user.c
// purpose:  is the representation of an interactive (user) in the MUD

#include <globals.h>

inherit BASE;
inherit COMMAND_OB;
inherit SAVABLE;
inherit "/inherit/verb/indirect_give";
inherit __DIR__ "user/terminal";
inherit __DIR__ "user/handler-stack";

private string old_input = "";
private string name;
private string cwd = "/";
private string room;
private int wizard;

private static int logged_in;
private int autosave = 1;

string save_filename();
int quiet_save();
void save();
int query_autosave();
void disable_autosave();
void load();
void quit();

void swap_out();

string query_cwd();
string query_name();
string query_in_room_name();
string query_target_string();
string query_reflexive();
int query_wizard();
void set_wizard(int wiz);
string query_room();
void set_room(mixed place);
void set_name(string arg);
int is_logged_in();
varargs void tell(string str, int indent);

void activate_interactive();
void setup();

varargs void move(mixed location, string leave, string arrive);
void process_command(string arg);

#ifdef __INTERACTIVE_CATCH_TELL__
void catch_tell(string str) {
    receive(str);
}
#endif

string save_filename() {
    return sprintf("/data/user/%s", query_name());
}

int quiet_save() {
    string savefile = save_filename();
    ensure_path_of_file_exists(savefile);
    store_inventory();

    return save_object(savefile);
}

void save() {
    if (quiet_save()) {
        tell("%^BOLD%^%^GREEN%^Saved.%^RESET%^\n");
    } else {
        tell("%^BOLD%^%^RED%^Error saving file.%^RESET%^\n");
    }
}

int query_autosave() {
    return autosave;
}

void disable_autosave() {
    autosave = 0;
}

void enable_autosave() {
    autosave = 1;
}

void load() {
    string fname = save_filename();
    if (sizeof(stat(fname + ".o"))) {
        restore_object(fname);
        load_inventory();
    }
}

void quit() {
    save();
    shout(color_surround("bold",
                sprintf("[ %s leaves the mud ]\n", query_name())));
}

void swap_out() {
    object new_user;

    if (find_object(USER_OB)) {
        destruct(find_object(USER_OB));
    }

    quiet_save();

    new_user = BIRTH_D->create_swapped_user(query_name(), this_object());

    if (new_user) {
        new_user->move(environment());
        new_user->load();
        new_user->tell("You feel different.\n");

        destruct(this_object());
    } else {
        this_object()->tell("Nothing happens.\n");
    }
}

string query_room() {
    if (!room) {
        room = START_ROOM;
    }
    return room;
}

void set_room(mixed place) {
    string filename;
    if (objectp(place)) {
        filename = file_name(place);
    } else if (stringp(place)) {
        filename = place;
    } else {
        return;
    }
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

string query_in_room_name() {
    return query_name();
}

string query_target_string() {
    return query_name();
}

string query_reflexive() {
    return "himself";
}

void
set_name(string arg)
{
//  may wish to add security to prevent just anyone from changing
//  someone else's name.
    name = arg;
    set_parse_ids(({ query_name() }));
}

int query_wizard() {
    return wizard;
}

void set_wizard(int wiz) {
    wizard = wiz;
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
    function prompt = query_prompt();
    function handler;
    if (!prompt) {
        handler = (: process_command :);
        prompt = (: tell("%^RESET%^> ") :);
        push_handler(handler, prompt);
    }
    evaluate(prompt);
}
#endif

varargs void tell(string str, int indent) {
    if (indent) {
        tell_object(this_object(), format(indent, "%s", str));
    } else {
        tell_object(this_object(), format(0, "%s", str));
    }
}

varargs void move(mixed location, string leave, string arrive) {
    ::move(location, leave, arrive);

    set_room(location);
    LOOK_D->player_glance(this_object());
}

void process_command(string arg) {
    mixed pre;

    if (arg == "!") {
        arg = old_input;
    } else {
        old_input = arg;
    }

    pre = query_prefix(arg[0]);
    if (pre) {
        arg = pre + " " + arg[1..];
    }
    if (trim(arg) == "stop") {
        clear_queue();
    } else {
        try_execute(arg);
    }
}

#ifdef __NO_ADD_ACTION__
void process_input(string arg) {
    handle_input(arg);
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
    ::create();
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

void activate_interactive() {
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
}

// setup: used to configure attributes that aren't known by this_object()
// at create() time such as living_name (and so can't be done in create()).

void setup() {
    activate_interactive();
    set_wizard(0);
    load();

    look_description = "This is " + query_name() + ".\n";

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
