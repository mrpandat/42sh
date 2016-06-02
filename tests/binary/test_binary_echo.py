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

    def test_07_echo_with_e_simple(self):
        a = execute_cmd("../42sh -c 'echo -e a'")
        b = execute_cmd("/bin/echo -e a")
        self.assertEqual(a.stdout, b.stdout)

    def test_08_echo_with_e_simple_c(self):
        a = execute_cmd("../42sh -c 'echo -e lol \c a'")
        b = execute_cmd("/bin/echo -e 'lol \c a'")
        self.assertEqual(a.stdout, b.stdout)

    def test_09_echo_with_e_escaped_simple(self):
        a = execute_cmd("../42sh -c 'echo -e \r'")
        b = execute_cmd("/bin/echo -e '\r'")
        self.assertEqual(a.stdout, b.stdout)

    def test_10_echo_with_e_escaped_medium(self):
        a = execute_cmd("../42sh -c 'echo -e a \t  \n'")
        b = execute_cmd("/bin/echo -e a \t  \n'")
        self.assertEqual(a.stdout, b.stdout)

    def test_11_echo_with_e_escaped_hard(self):
        a = execute_cmd("../42sh -c 'echo -e \\t'")
        b = execute_cmd("/bin/echo -e '\\t'")
        self.assertEqual(a.stdout, b.stdout)

    def test_12_echo_with_e_escaped_hardcore(self):
        a = execute_cmd("../42sh -c 'echo -e \\t \\n \\e \\c'")
        b = execute_cmd("/bin/echo -e '\\t \\n \\e \\c'")
        self.assertEqual(a.stdout, b.stdout)

    def test_13_echo_with_e_escaped_impossibru(self):
        a = execute_cmd("../42sh -c 'echo -e \\t ~ \\ \n | bn \\z'")
        b = execute_cmd("/bin/echo -e '\\t ~ \\ \n | bn \\z'")
        self.assertEqual(a.stdout, b.stdout)
