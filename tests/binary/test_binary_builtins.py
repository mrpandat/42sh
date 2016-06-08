import unittest
from test_functions import *

class TestBinaryLexer(unittest.TestCase):

    def test_1_exit_err(self):
        result = execute_cmd('../42sh -c "exit"')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 1)

    def test_2_exit(self):
        result = execute_cmd('../42sh -c "exit 43"')
        self.assertEqual(result.stdout, '')
        self.assertEquals(result.returncode, 43)

        def test_3_exit_error(self):
            self.assertEqual(execute_cmd_cmp('-c "exit fozhf"'), 0)