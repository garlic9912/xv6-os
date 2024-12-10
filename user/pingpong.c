#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int p1[2], p2[2];
    pipe(p1); 
    pipe(p2);
    int pid = fork();
    if (pid == 0) {
        // read pipe
        char buf[10];
        read(p1[0], buf, sizeof(buf));
        close(p1[0]);
        fprintf(1, "%d: received %s\n", getpid(), buf);
        // write pipe
        write(p2[1], "pong", strlen("pong"));
        close(p2[1]);
        exit(0);
    }
    else {
        // write pipe
        char buf[10];
        write(p1[1], "ping", strlen("ping"));
        close(p1[1]);
        wait((int *)0);
        // read pipe
        read(p2[0], buf, sizeof(buf));
        close(p2[0]);
        fprintf(1, "%d: received %s\n", getpid(), buf);
        exit(0);
    }
}