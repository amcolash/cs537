import toolspath
from testing import Xv6Build, Xv6Test

class Settickets(Xv6Test):
   name = "settickets"
   description = "compile and run a user program with a settickets call"
   tester = name + ".c"
   timeout = 30

class Getpinfo(Xv6Test):
   name = "getpinfo"
   description = "compile and run a user program with a getpinfo call"
   tester = name + ".c"
   timeout = 30

class Getpinfo2(Xv6Test):
   name = "getpinfo2"
   description = "check that getpinfo returns some reasonable values"
   tester = name + ".c"
   timeout = 30

class Ticks(Xv6Test):
   name = "ticks"
   description = "check that processes are scheduled at correct ratio"
   tester = name + ".c"
   timeout = 75
   make_qemu_args = "CPUS=1"

class Ticks2(Xv6Test):
   name = "ticks2"
   description = "check that processes are scheduled at correct ratio"
   tester = name + ".c"
   timeout = 75
   make_qemu_args = "CPUS=1"

class Ticks3(Xv6Test):
   name = "ticks3"
   description = "check that processes are scheduled at correct ratio"
   tester = name + ".c"
   timeout = 75
   make_qemu_args = "CPUS=1"

class Usertests(Xv6Test):
   name = "usertests"
   description = "run usertests to check for regressions"
   tester = name + ".c"
   timeout = 500

all_tests = [Settickets, Getpinfo, Getpinfo2, Ticks, Ticks2, Ticks3]

import toolspath
from testing.runtests import main
main(Xv6Build, all_tests)
