#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    
    if(argc != 2){
        printf("too few or too many arguments\n");
        exit(1);
    }
    for(int i = 0; argv[1][i] != 0; ++i){//align with 8 bytes, i.e. sizeof(argv[1]) == 8
        if(argv[1][i] > '9' || argv[1][i] < '0'){
            printf("No, you gave me a wrong argument\n");
            exit(1);
        }
    }
    int sleepTime = atoi(argv[1]);
    printf("(nothing happens for a little while)\n");
    sleep(sleepTime);
    exit(0);
    //return 0;
}
