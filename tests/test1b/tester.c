// Do not modify this file. It will be replaced by the grading scripts
// when checking your project.

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i = 0, pid;
  printf(1, "%s", "** Placeholder program for grading scripts **\n");
  printf(1, "%d\n", addnum(22675));
  for (i = 226; i <=245; ++i)
  {
    printf(1, "%d\n", addnum(i));
  }
  pid = fork();
  if (pid == 0) {
    printf(1, "%d\n", addnum(22675));
    for (i = 226; i <=245; ++i)
    {
        printf(1, "%d\n", addnum(i));
    }
    printf(1, "End of tests\n");
    while(1);
  }
  while(1);
  return(0);
}
