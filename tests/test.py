from test_functions import *
from static.colors import bcolors
from fun import *
import datetime
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

if __name__ == "__main__":
    for arg in sys.argv:
        print (arg)
        if arg == "-l" or arg =="--list":
            print ("categories")
        if arg == "-c":
            print("execute category")
        if arg == "-s" or arg=="--sanity":
            print ("valgrind")
    #unittest.main()
    now = datetime.datetime.now()
    os.chdir(os.path.dirname(os.path.realpath(__file__)))

    print_colored("./static/nyan")


