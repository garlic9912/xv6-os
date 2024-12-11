#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void prime_sieve(int fd[2]) {    
    // prime is the first num
    close(fd[1]);
    int prime;
    if (read(fd[0], &prime, sizeof(int)) == 0)
        return;
    fprintf(1, "prime %d\n", prime);
    // recursion
    int p[2];
    pipe(p);
    int pid = fork();
    if (pid == 0) {
        prime_sieve(p);
    }
    else {
        // sieve
        close(p[0]);
        int num;
        while (read(fd[0], &num, sizeof(int)) > 0) {
            if (num % prime == 0) continue;
            write(p[1], &num, sizeof(int));
        }
        close(fd[0]);
        close(p[1]);
        wait((int *)0);
        exit(0);
    } 
}


int main(void) {
    int p[2];
    pipe(p);
    int pid = fork();
    if (pid == 0) {
        prime_sieve(p);
    } 
    else {
        close(p[0]);
        for (int i = 2; i <= 35; i++) {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait((int *)0);
    }
    exit(0);
}