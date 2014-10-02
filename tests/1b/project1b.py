import toolspath
from testing import Xv6Build, Xv6Test

class Basic(Xv6Test):
   name = "basic"
   description = "call getsyscallinfo() from a user program"
   tester = "basic.c"
   make_qemu_args = "CPUS=1"

class Getsyscallinfo(Xv6Test):
   name = "getsyscallinfo"
   description = "repeated calls of getsyscallinfo()"
   tester = "getsyscallinfo.c"
   make_qemu_args = "CPUS=1"

class Many(Xv6Test):
   name = "many"
   description = "count many other syscalls"
   tester = "many.c"
   make_qemu_args = "CPUS=1"

class Invalid(Xv6Test):
   name = "invalid"
   description = "make an invalid system call"
   tester = "invalid.c"
   make_qemu_args = "CPUS=1"

class Usertests(Xv6Test):
   name = "usertests"
   description = "run usertests to check for regressions"
   tester = "usertests.c"
   timeout = 300

import toolspath
from testing.runtests import main
main(Xv6Build, [Basic, Getsyscallinfo, Many, Invalid])
