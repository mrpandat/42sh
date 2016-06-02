import unittest
from test_functions import *

class TestCommands(unittest.TestCase):

    def test_01_simple_case_command(self):
        self.assertEqual(execute_cmd_cmp("case word in wor) /bin/echo mdr;; word) /bin/echo lol;; esac"), 0)