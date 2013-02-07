int main(string dir) {

    int window_width = 80;
    int TAB_WIDTH = 8;

    string *files = get_dir(dir);
    int numfiles = sizeof(files);

    string current;
    int longest_length = 0;
    int highest_tabwidth;
    int column_count;

    int len;
    int name_length;
    int i, j;
    int this_tab_width;
    int tabs_to_print;

    foreach (current in files) {

	len = strlen(current);
	if (len > longest_length) {
	    longest_length = len;
	}
    }

    highest_tabwidth = (longest_length + 1) / TAB_WIDTH + 1;

    column_count = window_width / (highest_tabwidth * TAB_WIDTH);

    for (i = 0; i < numfiles; i++) {

	name_length = strlen(files[i]);
	write(files[i]);

	if (i % column_count == column_count - 1) {
	    write("\n");
	} else {
	    this_tab_width = name_length / TAB_WIDTH;
	    tabs_to_print = 0 + highest_tabwidth - this_tab_width;

	    for (j = 0; j < tabs_to_print; j++) {
		write("\t");
	    }
	}
    }
    write("\n");

    return 0;
}
