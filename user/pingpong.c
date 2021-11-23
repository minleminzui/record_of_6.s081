#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p1[2], p2[2];//p1子进程读，父进程写，p2反之
    pipe(p1);
    pipe(p2);

    char *byt = "x";
    int len = sizeof(byt);
    if(fork() == 0){
        // close(p1[1]);
        // close(p2[0]);//不关也没关系
        if(write(p2[1], byt, len) != len){
            printf("child write with mistakes");
            exit(1);
        }
        if(read(p1[0], byt, len) != len){
            printf("child read with mistakes");
            exit(1);
        }
        
        printf("%d: received ping\n", getpid());
        exit(0);
    }else{
        // close(p1[0]);
        // close(p2[1]);
        if(write(p1[1], byt, len) != len){
            printf("parent write with mistakes\n");
            exit(1);
        }
        
        if(read(p2[0], byt,len) != len){
            printf("parent read with mistakes\n");
            exit(1);
        }
        wait(0);
        printf("%d: received pong\n", getpid());
    }
    
    exit(0);
}
