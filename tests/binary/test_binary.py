import unittest
from test_functions import *

class TestBinary(unittest.TestCase):

    def test_01_noarg(self):
        result = execute_cmd('../42sh')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 0)
        self.assertTrue(sanity_test_cmd("../42sh"));

    def test_02_index(self):
        result = execute_cmd('../42sh -v')
        self.assertEqual(result.stdout, "Version 0.8\n")
        self.assertEquals(result.returncode, 0)
        self.assertTrue(sanity_test_cmd('../42sh -v'));

    def test_03_expandable_options(self):
        result = execute_cmd('../42sh --ver')
        self.assertEqual(result.stdout, "Version 0.8\n")
        self.assertEquals(result.returncode, 0)
        self.assertTrue(sanity_test_cmd('../42sh --ver'));


    def test_04_long_options(self):
        result = execute_cmd('../42sh --version')
        self.assertEqual(result.stdout, "Version 0.8\n")
        self.assertEquals(result.returncode, 0)
        self.assertTrue(sanity_test_cmd('../42sh --version'));


    def test_05_help(self):
        result = execute_cmd('../42sh -h')
        self.assertEqual(result.stdout, "42sh [ GNU long options ] [ options ] [ file ]\n")
        self.assertEquals(result.returncode, 0)
        self.assertTrue(sanity_test_cmd('../42sh -h'));


    def test_06_norc(self):
        result = execute_cmd('../42sh --norc')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 0)
        self.assertTrue(sanity_test_cmd('../42sh --norc'));


    def test_07_ast_print(self):
        result = execute_cmd('../42sh --ast-print')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 0)
        self.assertTrue(sanity_test_cmd('../42sh --ast-print'));

    def test_08_shopt_1(self):
        result = execute_cmd('../42sh -O dotdadglob')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 2)
        self.assertTrue(sanity_test_cmd('../42sh -O dotdadglob'));

    def test_09_shopt_2(self):
        result = execute_cmd('../42sh +O dodazdztglob')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 2)
        self.assertTrue(sanity_test_cmd('../42sh +O dodazdztglob'));

    def test_10_inexistant_script(self):
        result = execute_cmd('../42sh inexistent.sh')
        self.assertEqual(result.stderr, 'No such file or directory\n')
        self.assertEquals(result.returncode, 127)
        self.assertTrue(sanity_test_cmd('../42sh inexistent.sh'));

    def test_11_inexistant_command(self):
        self.assertEqual(execute_cmd("../42sh foiehofihe").returncode, 127)
        self.assertTrue(sanity_test_cmd("../42sh foiehofihe"));

    def test_12_inexistant_command_wth_arg(self):
        self.assertEqual(execute_cmd('../42sh -c "foiehofihe '
                                     'efopjf" ').returncode, 127)
        self.assertTrue(sanity_test_cmd('../42sh -c "foiehofihe efopjf"'));

    def test_13_existant_command(self):
        self.assertEqual(execute_cmd_cmp("/bin/echo"), 0)

    def test_14_existant_command_wth_arg(self):
        self.assertEqual(execute_cmd_cmp("/bin/echo yolo"), 0)

    def test_15_shopt_3(self):
        result = execute_cmd('../42sh -O dotglob')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 0)
        self.assertTrue(sanity_test_cmd('../42sh -O dotglob'));

    def test_16_shopt_4(self):
        result = execute_cmd('../42sh +O dotglob')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 0)
        self.assertTrue(sanity_test_cmd('../42sh +O dotglob'));
