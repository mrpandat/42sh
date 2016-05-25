from test_functions import *
from static.colors import bcolors
from fun import *
import datetime
import unittest
import os
import subprocess
from cffi import FFI


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
    unittest.main()

    now = datetime.datetime.now()
    os.chdir(os.path.dirname(os.path.realpath(__file__)))

    print_colored("./static/nyan")


