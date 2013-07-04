
#include <globals.h>

int main(string arg) {
    object user;

    printf("%-25s  idle\n", "name (*edit, +input)");
    printf("---------------------     -----\n");
    foreach (user in users()) {
        printf("%-25s %4dm\n", (string)user->query_name() +
                (in_edit(user) ? "*" : "") +
                (in_input(user) ? "+" : ""),
                query_idle(user) / 60
        );
    }
    return 1;
}
