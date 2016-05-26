import unittest
from cffi import FFI
from test_functions import *

class TestBinary(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()

    def test_01_index(self):
        result = execute_cmd('./42sh -v')
        self.assertEqual(result.stdout, "Version 0.5\n")


    def test_02_index(self):
        result = execute_cmd('./42sh --version')
        self.assertEqual(result.stdout, "Version 0.5\n")
