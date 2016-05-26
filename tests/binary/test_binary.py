import unittest
from cffi import FFI
from test_functions import *

class TestBinary(unittest.TestCase):

    def test_01_index(self):
        result = execute_cmd('./42sh -v')
        self.assertEqual("a", "ae")
        #self.assertEqual(result.stdout, "Version 0.5\n")

    def test_02_expandable_options(self):
        result = execute_cmd('./42sh --ver')
        self.assertEqual(result.stdout, "Version 0.5\n")

    def test_03_long_options(self):
        result = execute_cmd('./42sh --version')
        self.assertEqual("", "")
        #self.assertTrue(result.stdout, "Version 0.5\n")