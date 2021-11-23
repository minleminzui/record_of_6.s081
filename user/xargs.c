#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int 
main(int argc, char *argv[]) 
{
    char *paras[MAXARG];
    char buf[512];
    if(argc < 2 || argc + 1 > MAXARG){
        printf("No,too many or few arguments\n");
        exit(1);
    }
    for(int i = 1; i < argc; ++i){
        paras[i - 1] = argv[i];
    }
    while(1){
        int i = 0;
        while(read(0, &buf[i], 1) > 0){
            if(buf[i] == '\n') break;
            ++i;
        }
        if(i == 0) break;
        buf[i] = 0;
        paras[argc - 1] = buf;
        if(fork() == 0){
            exec(argv[1], paras);
            exit(0);
        }
        wait(0);
    }
    exit(0);
}