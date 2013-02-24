
#include <globals.h>

inherit "/inherit/error_out";

void old_password(string pass);
void new_password(string pass);
void confirm_password(string pass, string first);

int main(string arg) {
    if (arg && strlen(arg)) {
        return error_out("Changing others' passwords not implemented yet.");
    }

    write("Current password: ");
    input_to("old_password", 1);
}

string password_file() {
    return "/u/passwords/" + this_player()->query_name();
}

void old_password(string pass) {
    string encrypted = encrypt(pass);
    string accepted = read_file(password_file(), 1, 1);

    accepted = replace_string(accepted, "\n", "");

    if (encrypted == accepted) {
        write("\nNew password: ");
        input_to("new_password", 1);
    } else {
        error_out("\nWrong password.");
    }
}

void new_password(string pass) {
    string encrypted = encrypt(pass);

    write("\nConfirm: ");
    input_to("confirm_password", 1, encrypted);
}

void confirm_password(string pass, string crypt_first) {
    if (encrypt(pass) == crypt_first) {
        write_file(password_file(), crypt_first, 1);
        write("\n");
    } else {
        error_out("\nPasswords do not match.");
    }
}
