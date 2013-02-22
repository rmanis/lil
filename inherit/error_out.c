
int error_out(string str);

int error_out(string str) {
#ifndef __NO_ADD_ACTION__
        return notify_fail(str + "\n");
#else
        output("%s\n", str);
        return 0;
#endif
}
