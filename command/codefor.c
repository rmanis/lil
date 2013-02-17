int
main(string a)
{
    object ret;
    mixed code;

    if (file_size("/eval/tmp_eval_file.c") != -1)
    rm ("/eval/tmp_eval_file.c");
    if (find_object("/eval/tmp_eval_file"))
    destruct(find_object("/eval/tmp_eval_file"));

    write_file("/eval/tmp_eval_file.c", "mixed eval() { " + a + "; }\n");

    ret = load_object("/eval/tmp_eval_file");

    dump_prog(ret, 1, "/eval/CODE_TMP_FILE");
    code = read_file( "/eval/CODE_TMP_FILE");
    rm("/eval/CODE_TMP_FILE");
    rm("/eval/tmp_eval_file.c");

    code = explode(code, ";;;  *** Disassembly ***\n");
    code = code[1];
    write(code[0..strlen(code)-1]);
    return 1;
}
