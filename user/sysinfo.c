#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 1){
      printf("No,too few or many arguments!!!\n");
      exit(1);
  }
  struct sysinfo sinfo;
  sysinfo(&sinfo);
  printf("free mem: %d\nunused pro: %d\n", sinfo.freemem, sinfo.nproc);
  //%u或者%llu并不能得到满意的结果  
  exit(0);
}

