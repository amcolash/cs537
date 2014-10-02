tester_files = ["rand"]
import sys, os

import toolspath
from testing import BuildTest

build_test = BuildTest
build_test.targets = ["libmem.so"]
all_tests = __import__("rand").test_list

from testing.runtests import main
main(build_test, all_tests)
