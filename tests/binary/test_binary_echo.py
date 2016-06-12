import unittest

from test_functions import *


def executeEcho(str):
    a = execute_cmd("../42sh -c \"echo " + str + "\"")
    b = execute_cmd("/bin/echo " + str)
    if a.stdout != b.stdout:
        print("ref: " + b.stdout)
        print("got: " + a.stdout)
    return (a.stdout == b.stdout)


def executeEchoSanity(str):
    return (
    executeEcho(str) and sanity_test_cmd("../42sh -c \"echo " + str + "\""))


class TestBinaryEcho(unittest.TestCase):
    def test_01_echo_simple(self):
        self.assertTrue(executeEchoSanity("ok"))

    def test_02_echo_multiple(self):
        self.assertTrue(executeEcho("ok ok ok"))

    def test_03_echo_with_option_n(self):
        self.assertTrue(executeEcho("-n ok"))

    def test_04_echo_multiple_with_option_n(self):
        self.assertTrue(executeEchoSanity("-n ok ok ok"))

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

    def test_07_echo_backslashed(self):
        self.assertTrue(executeEcho("\\t"))

    def test_08_echo_e(self):
        self.assertTrue(executeEcho("-e \\t"))

    def test_09_echo_quoted(self):
        self.assertTrue(executeEchoSanity("\'\\t\'"))

    def test_10_echo_e_quoted(self):
        self.assertTrue(executeEcho("-e \'\\t\'"))

    def test_11_echo_multiple(self):
        self.assertTrue(executeEcho("\\t \\t"))

    def test_12_echo_e_multiple(self):
        self.assertTrue(executeEchoSanity("-e \\t \\t"))

    def test_13_echo_quoted_multiple(self):
        self.assertTrue(executeEcho("\'\\t \\t\'"))

    def test_14_echo_e_quoted_multiple(self):
        self.assertTrue(executeEcho("-e \'\\t \\t\'"))

    def test_15_echo_e_quoted_multiple_stuck(self):
        self.assertTrue(executeEchoSanity("-e \'\\ta\\ta\\t\\t\'"))

    def test_16_echo_multiple_options(self):
        self.assertTrue(executeEcho("-e -n \' a\\ta\'"))

    def test_17_echo_multiple_options_factor(self):
        self.assertTrue(executeEcho("-en \' a\\ta\'"))

    def test_18_echo_multiple_options_factor_backslashed(self):
        self.assertTrue(executeEchoSanity("-en \'troubad\\our\'"))
