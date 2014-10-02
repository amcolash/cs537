// Do not modify this file. It will be replaced by the grading scripts
// when checking your project.

#include "types.h"
#include "stat.h"
#include "user.h"

#define FAIL(x)\
   printf(1, "failed: %s\n", x);\
   exit();\

/* Created this macro to increase confidence in whether a test is passing
 * or failing. If they count too few system calls for a test, then it definitely
 * failed. If they count too many, it may be because another process got CPU
 * time and made additional system call/s.
 *
 * I am aware that this now means when we test open("file", 0), we end up
 * opening the file several times, and when we close a file descriptor, we follow that
 * by closing it another several times. We don't really care for the success of the
 * calls, just that they happen.
 */
#define SEVERAL 3
#define TEST(CODE, EXPECTED, MSG) \
  printf(1, "calling (%s), should count %d syscalls\n", MSG, EXPECTED);\
  failed = passed = 0;\
  for(i = 0; i < SEVERAL; i++) {\
    before = getsyscallinfo();\
    CODE;\
    after = getsyscallinfo() - 1;\
    printf(1, "%d) counted %d syscalls\n", i+1, after-before);\
    if(after - before < EXPECTED) { FAIL("count too low"); }\
    else if(after - before == EXPECTED) { passed++; }\
    else { failed++; }\
  }\
  if (failed > passed) { FAIL("count consistently too high"); };

int
main(int argc, char *argv[])
{
  int i, failed, passed;
  int before, after;

  // fork, exit, wait (kind of hard to test after a fork otherwise due to race conditions)
  int pid;
  TEST(pid = fork(); if(pid == 0) exit(); else wait();, 3, "fork, exit, wait");

  // pipe
  int fd[2];
  TEST(pipe(fd);, 1, "pipe");
  
  // write
  TEST(write(fd[1], "hello", 5);, 1, "write");

  // read
  char str[5];
  TEST(read(fd[0], str, 1);, 1, "read");

  // close
  TEST(close(fd[0]); close(fd[1]);, 2, "close, close");

  // fork, kill
  TEST(pid = fork(); if(pid == 0) while(1); else kill(pid);, 2, "fork, kill");

  // getpid
  TEST(pid = getpid();, 1, "getpid");

  // sleep
  TEST(sleep(10);, 1, "sleep");

  // uptime
  before = getsyscallinfo();
  TEST(uptime();, 1, "uptime");

  // open, dup
  TEST(fd[0] = open("syscalltest.txt", 0); fd[1] = dup(fd[0]);, 2, "open, dup");

  // fstat
  struct stat fs;
  TEST(fstat(fd[0], &fs);, 1, "fstat");

  // mkdir
  TEST(mkdir("syscalltest");, 1, "mkdir");

  // chdir
  TEST(chdir("syscalltest");, 1, "chdir");

  // link
  TEST(link("syscalltest2.txt", "../syscalltest.txt");, 1, "link");

  // unlink
  TEST(unlink("syscalltest2.txt");, 1, "unlink");

  // now remove the directory we created
  chdir("..");
  unlink("syscalltest");

  // failed exec
  char* execargs[1];
  execargs[0] = "notactuallythenameofanexecutable";
  TEST(pid = exec(execargs[0], execargs);, 1, "exec");

  // mknod
  TEST(mknod("syscalltest", 1, 1);, 1, "mknod");
  unlink("syscalltest");

  // sbrk
  TEST(sbrk(0);, 1, "sbrk");

  printf(1, "TEST PASSED");
  exit();
}
