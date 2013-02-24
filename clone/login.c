#include <globals.h>

void login_prompt();
void handle_username(string username, int tries);
void create_new_user(string yes_no, string username);
void handle_password(string password, string user, int tries);
private void ensure_no_user(string user);
private void successful_login(string user);
private void create_user_object(string name);
private void ensure_passwords_folder();
private string password_file(string name);
private int user_exists(string name);
void reject();

#ifdef __INTERACTIVE_CATCH_TELL__
void catch_tell(string str) {
    receive(str);
}
#endif

void logon() {

#ifdef __NO_ADD_ACTION__
    set_this_player(this_object());
#endif

    // create_user_object("stuf" + "_" + getoid(this_object()));
    cat("/etc/login_msg");
    login_prompt();

#ifdef __PACKAGE_UIDS__
    seteuid(getuid(this_object()));
#endif

}

void login_prompt() {
    output("Name: ");
    input_to("handle_username", 0, 0);
}

void handle_username(string username, int tries) {
    string luser = lower_case(username);

    if (strlen(username) == 0) {
	reject();
    } else if (user_exists(luser)) {
	output("Password: ");
	input_to("handle_password", 1, luser, tries);
    } else {
	output("User '%s' does not exist.  Create (y/n) ? ", luser);
	input_to("create_new_user", 0, luser);
    }
}

void create_new_user(string yes_no, string username) {
    string yn = lower_case(yes_no);

    if (yn[0] == 'y') {
	output("Creating user '%s'\n", username);
	output("Password: ");
	input_to("create_password", 1, username);
    } else {
	output("Okay, we'll try again.\n");
	login_prompt();
    }
}

void handle_password(string password, string user, int tries) {
    string input_key = encrypt(password);
    string accepted_key = read_file(password_file(user), 1, 1);

    output("\n");

    if (strlen(password) == 0) {
	reject();
    } else if (input_key == accepted_key) {
	successful_login(user);
    } else {
	output("Wrong password\n");
	handle_username(user, tries + 1);
    }
}

void create_password(string password, string username) {
    string key = encrypt(password);

    output("\n");

    ensure_passwords_folder();
    ensure_no_user(username);

    write_file(password_file(username), key);
    successful_login(username);
}

private void ensure_no_user(string user) {
    string file = password_file(user);
    if (sizeof(stat(file))) {
	output("Ruh-roh!  We're overwriting %s's password\n", user);
	rm(file);
    }
}

private void successful_login(string user) {
    cat("/etc/motd");
    create_user_object(user);
}

private void create_user_object(string name) {
    object user;

    string error = catch {
        user = new("/clone/user");
        user->set_name(name);
        exec(user, this_object());
        user->setup();

#ifndef __NO_ENVIRONMENT__
        user->teleport_to(user->get_room(),
                format(color_surround("green", "%s enters the mud.\n"),
                    name),
                1);
#endif
        shout(format("%^BOLD%^[ %s enters the mud ]%^RESET%^\n", name));
    };

    if (error) {
        write("Error occurred while creating user object.\n");
    }

    destruct(this_object());
}

void reject() {
    output("Rejected.  Goodbye.\n\n");
    remove_interactive(this_object());
}

// Thanks to
// http://startfromlil.wordpress.com/2012/04/04/users-and-passwords/

// A function to ensure the passwords folder exists.
// This will only matter the first time a user is created,
// but let's go ahead and write robust code.
private void ensure_passwords_folder () {
    if ( sizeof( stat( "/u/passwords" ) ) == 0 ) {
        mkdir( "/u/passwords" );
    }
}

// A function that embodies the password file naming convention.
// The parameter is the character's name (e.g., "Dave").
private string password_file ( string name ) {
    return "/u/passwords/" + name;
}

// A function that determines if the user exists, based on
// whether a password file for that user exists.
private int user_exists ( string name ) {
    return sizeof( stat( password_file( name ) ) ) > 0;
}
