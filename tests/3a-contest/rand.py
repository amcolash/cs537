import pickle, os

import toolspath
from testing import Test

class RandomTest(Test):
   name = "random"
   description = "psuedo-random sequence of allocs and frees"
   timeout = 20
   seed = 0
   n = 10
   write = 0
   def run(self):
      child = self.runexe([os.path.join(self.test_path, "random"),
         str(self.seed), str(self.n), str(self.write)],
         status = 0)
      self.log("time: " + str(child.wallclock_time))
      self.done()

class Random2Test(RandomTest):
   name = "random2"
   seed = 0
   n = 1000
   write = 1

class Random3Test(RandomTest):
   name = "random3"
   seed = 0
   n = 100000
   write = 1

class Random4Test(RandomTest):
   name = "random4"
   seed = 1
   n = 500000
   write = 1

class Random5Test(RandomTest):
   name = "random5"
   seed = 1
   n = 2000000
   write = 0
   timeout = 50

def median(vals):
   if len(vals) % 2 == 1:
      return vals[(len(vals) + 1)/ 2 - 1]
   else:
      a = vals[len(vals)/2-1]
      b = vals[len(vals)/2]
      return (a + b) / 2


class Contest(Test):
   name = "contest"
   description = "contest"
   seeds = [1, 2, 3]
   n = 20000000
   write = 0
   timeout = 180

   def run(self):
      times = list()
      for seed in self.seeds:
         child = self.runexe([os.path.join(self.test_path, "random"),
            str(seed), str(self.n), str(self.write)],
            status = 0)
         self.log("time: " + str(child.wallclock_time))
         times.append(child.wallclock_time)

      with open("times.pickle", "wb") as f:
         pickle.dump(times, f)

      times = sorted(times)
      print "best  ", times[0]
      print "median", median(times)
      print "worst ", times[-1]
      self.done()

test_list = [Contest]
