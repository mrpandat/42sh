import unittest
from test_functions import *

class TestBinary_cd(unittest.TestCase):

    def test_01_noarg(self):
        self.assertEqual(execute_cmd_cmp('../42sh -c "cd"'), 0)
    def test_02_arg(self):
        self.assertEqual(execute_cmd_cmp('../42sh -c "cd src"'), 0)
    def test_03_cdminus(self):
        self.assertEqual(execute_cmd_cmp('../42sh -c "cd -"'), 0)
    def test_04_cdpwd(self):
        self.assertEqual(execute_cmd_cmp('../42sh -c "cd /bin && pwd"'), 0)
    def test_05_cdnoargpwd(self):
        self.assertEqual(execute_cmd_cmp('../42sh -c "cd && /bin/pwd"'), 0)
    def test_06_cdminuspwd(self):
        self.assertEqual(execute_cmd_cmp('../42sh -c "cd - && /bin/pwd"'), 0)
