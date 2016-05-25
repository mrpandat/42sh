import unittest
from cffi import FFI
from test_functions import *

class TestLexer(unittest.TestCase):
    def __init__(self,arg):
        unittest.TestCase.__init__(self,arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def test_01_index(self):
        idx = self.lib.test()
        self.assertEqual(idx, 1)

