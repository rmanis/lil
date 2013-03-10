int
main(string arg)
{
    string start;
    string end;
    mixed result;
    /* clean up first */
    if (file_size("/eval/tmp_eval_file.c") != -1)
    rm ("/eval/tmp_eval_file.c");
    if (find_object("/eval/tmp_eval_file"))
    destruct(find_object("/eval/tmp_eval_file"));

    start = read_file("/eval/header");
    end = read_file("/eval/footer");

    if (strlen(arg) > 0) {
        write_file("/eval/tmp_eval_file.c",start + arg + end);
        result = "/eval/tmp_eval_file"->eval();
        if (previous_object()) {
            previous_object()->tell(sprintf("Result = %O\n", result));
        }
    }

    return 1;
}
