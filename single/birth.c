
object create_user(string name, object mother);
object create_swapped_user(string name, object mother);

object create_user(string name, object mother) {
    object user;
    user = create_swapped_user(name, mother);

    if (user) {
        user->setup();
    }

    return user;
}

object create_swapped_user(string name, object mother) {
    object user;
    string error = catch {
        user = new("/clone/user");
        user->set_name(name);
        exec(user, mother);
        user->activate_interactive();
    };

    if (error) {
        write("Error occurred while creating user object.\n");
    }
    return user;
}
