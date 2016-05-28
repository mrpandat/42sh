import unittest
from test_functions import *

class TestBinary(unittest.TestCase):

    def test_01_noarg(self):
        result = execute_cmd('../42sh')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 0)

    def test_02_index(self):
        result = execute_cmd('../42sh -v')
        self.assertEqual(result.stdout, "Version 0.5\n")
        self.assertEquals(result.returncode, 0)

    def test_03_expandable_options(self):
        result = execute_cmd('../42sh --ver')
        self.assertEqual(result.stdout, "Version 0.5\n")
        self.assertEquals(result.returncode, 0)

    def test_04_long_options(self):
        result = execute_cmd('../42sh --version')
        self.assertEqual(result.stdout, "Version 0.5\n")
        self.assertEquals(result.returncode, 0)

    def test_05_help(self):
        result = execute_cmd('../42sh -h')
        self.assertEqual(result.stdout, "42sh [ GNU long options ] [ options ] [ file ]\n")
        self.assertEquals(result.returncode, 0)

    def test_06_norc(self):
        result = execute_cmd('../42sh --norc')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 0)

    def test_07_ast_print(self):
        result = execute_cmd('../42sh --ast-print')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 0)

    def test_08_shopt_1(self):
        result = execute_cmd('../42sh -0 dotglob')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 0)

    def test_08_shopt_2(self):
        result = execute_cmd('../42sh +0 dotglob')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 0)

   


