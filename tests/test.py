from test_functions import *
from fun import print_colored
import unittest
import os
from cffi import FFI
import sys

class Test(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def test_01_index(self):
        proc = execute_cmd("git shortlog -s | wc -l")
        self.assertEqual(proc.stdout.strip(), '4')

    def test_02_index(self):
         idx = self.lib.test()
         self.assertEqual(idx, 1)


def launch_all() :
    unittest.main()
    os.chdir(os.path.dirname(os.path.realpath(__file__)))

if __name__ == "__main__":
    sys.argv[0] = ""
    for arg in sys.argv:
        if arg=="":
            continue
        elif arg == "-l" or arg =="--list":
            print ("categories")
            exit(0)
        elif arg == "-c":
            print("execute category")
            exit(0)
        elif arg == "-s" or arg=="--sanity":
            print ("valgrind")
            exit(0)
        else:
            print ("Unknow option : " + arg)
            exit(1)
    launch_all()




