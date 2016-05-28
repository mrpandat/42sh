import unittest
from cffi import FFI
from test_functions import *

class TestBinary(unittest.TestCase):

    def test_01_index(self):
        result = execute_cmd('./42sh -v')
        self.assertEqual(result.stdout, "Version 0.5\n")

    def test_02_expandable_options(self):
        result = execute_cmd('./42sh --ver')
        self.assertEqual(result.stdout, "Version 0.5\n")

    def test_03_long_options(self):
        result = execute_cmd('./42sh --version')
        self.assertTrue(result.stdout, "Version 0.5\n")

    def test_04_help(self):
        result = execute_cmd('./42sh -h')
        self.assertTrue(result.stdout, "42sh [ GNU long options ] [ options ] [ file ]\n")
        self.assertTrue(result.returncode, 0)

