import unittest

from test_functions import *


def executeEcho(str):
    a = execute_cmd("../42sh -c \"echo " + str + "\"")
    b = execute_cmd("/bin/echo " + str)
    if a.stdout != b.stdout:
        print("ref: " + b.stdout)
        print("got: " + a.stdout)
    return (a.stdout == b.stdout
    and sanity_test_cmd("../42sh -c \"echo " + str + "\""))


class TestBinaryEcho(unittest.TestCase):
    def test_01_echo_simple(self):
        self.assertTrue(executeEcho("ok"))

    def test_02_echo_multiple(self):
        self.assertTrue(executeEcho("ok ok ok"))

    def test_03_echo_with_option_n(self):
        self.assertTrue(executeEcho("-n ok"))

    def test_04_echo_multiple_with_option_n(self):
        self.assertTrue(executeEcho("-n ok ok ok"))

    def test_05_echo_version(self):
        a = execute_cmd("../42sh -c 'echo --version'")
        b = execute_cmd("/bin/echo --version")
        self.assertEqual(a.returncode, b.returncode)
        self.assertTrue(sanity_test_cmd("../42sh -c 'echo --version'"))

    def test_06_echo_help(self):
        a = execute_cmd("../42sh -c 'echo --help'")
        b = execute_cmd("/bin/echo --help")
        self.assertEqual(a.returncode, b.returncode)
        self.assertTrue(sanity_test_cmd("../42sh -c 'echo --help'"))


    def test_07_echo_special(self):
        self.assertTrue(executeEcho("\\t"))

    def test_08_echo_e_special(self):
        self.assertTrue(executeEcho("-e \\t"))

    def test_09_echo_special_quoted(self):
        self.assertTrue(executeEcho("\'\\t\'"))

    def test_10_echo_special_e_quoted(self):
        self.assertTrue(executeEcho("-e \'\\t\'"))

    def test_11_echo_special_multiple(self):
        self.assertTrue(executeEcho("\\t \\t"))

    def test_12_echo_e_special_multiple(self):
        self.assertTrue(executeEcho("-e \\t \\t"))

    def test_13_echo_special_quoted_multiple(self):
        self.assertTrue(executeEcho("\'\\t \\t\'"))

    def test_14_echo_special_e_quoted_multiple(self):
        self.assertTrue(executeEcho("-e \'\\t \\t\'"))