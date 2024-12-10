#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    // 至少需要两个参数
    if (argc < 2) {
        fprintf(2, "Usage: sleep ticks\n");
        exit(1);
    }
    // 调用系统调用
    sleep(atoi(argv[1]));
    exit(0);
}