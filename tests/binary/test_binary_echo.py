import unittest

from test_functions import *


class TestBinaryEcho(unittest.TestCase):
    def test_01_echo_simple(self):
        self.assertEqual(execute_cmd_cmp("echo ok"), 0)

    def test_02_echo_multiple(self):
        self.assertEqual(execute_cmd_cmp("echo ok ok ok"), 0)

    def test_03_echo_with_option_n(self):
        self.assertEqual(execute_cmd_cmp("echo -n ok"), 0)

    def test_04_echo_multiple_with_option_n(self):
        self.assertEqual(execute_cmd_cmp("echo -n ok ok ok"), 0)

    def test_05_echo_version(self):
        a = execute_cmd("../42sh -c 'echo --version'")
        b = execute_cmd("/bin/echo --version")
        self.assertEqual(a.returncode, b.returncode)

    def test_06_echo_help(self):
        a = execute_cmd("../42sh -c 'echo --help'")
        b = execute_cmd("/bin/echo --help")
        self.assertEqual(a.returncode, b.returncode)
