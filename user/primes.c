#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int *num_to_35;
void sieve(int len){
    
    int prime = num_to_35[0], p[2];
    
    printf("prime %d\n", prime);
    if(len == 1) exit(0);
    pipe (p);
    // close(p[1]);
    // close(p[0]);//the end of pipe for write in parent should be closed, or the child which reading from pipe will never stop reading 
    if(fork() == 0){
        close(p[0]);
        for(int i = 1; i < len; ++i){
            // printf("%d %d\n", i, *(num_to_35 + i));
            if(num_to_35[i] % prime != 0){
                write(p[1], num_to_35 + i, sizeof(int));
            }
        }
        close(p[1]);
        exit(0);
    }
    wait(0);
    close(p[1]);
    // close(p[0]);
    if(fork() == 0){
        close(p[1]);
        int *buf = malloc(sizeof(int));
        int tem_len = 0;
        while(read(p[0], buf, sizeof(int))){
            // printf("%d\n", *buf);
            num_to_35[tem_len++] = *buf;
        }
        // printf("are you out?");
        sieve(tem_len);
        close(p[0]);
        exit(0);
    }
    wait(0);
    exit(0);
}
int
main(int argc, char *argv[])
{
    int len = 35 - 2 + 1;
    num_to_35 = malloc(sizeof(int) * (len));
    for(int i = 2; i <= 35; ++i){
        num_to_35[i - 2] = i;
    }
    sieve(len);
    free(num_to_35);
    exit(0);
}
