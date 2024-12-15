#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    char c;
    int p = 0;
    char buf[512];
    char *new_argv[MAXARG];
    for (int i = 1; i < argc; i++) {
        new_argv[i-1] = argv[i];
    }
    // read the output from shell for every single line
    while (read(0, &c, 1) > 0) {
        // read until char '\n'
        if (c == '\n') {
            buf[p++] = 0;
            new_argv[argc-1] = buf;
            // exec the command with extra argument
            if (fork() == 0) {
                exec(argv[1], new_argv);
                exit(0);
            }
            else {
                wait((int *)0);
                p = 0;
            }
            continue;
        }
        buf[p++] = c;
    }
    exit(0);
}