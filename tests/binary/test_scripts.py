import unittest

from static.colors import bcolors
from test_functions import *


class TestBinary(unittest.TestCase):
    def exec_script(self, command):
        a = execute_cmd("../42sh " + command)
        b = execute_cmd("./" + command)
        msg = ("\nref: stdout: " + a.stdout + " stderr: " + a.stderr + " returncode: " + str(a.returncode))
        msg += ("\ngot: stdout: " + b.stdout + " stderr: " + b.stderr + " returncode: " + str(b.returncode))
        self.assertTrue(a.stdout == b.stdout and a.returncode == b.returncode, msg=msg)

    def test_01(self):
        self.exec_script("binary/scripts/test1.sh")

    def test_02(self):
        self.exec_script("binary/scripts/test2.sh")

    def test_03(self):
        self.exec_script("binary/scripts/test3.sh")

    def test_04(self):
        self.exec_script("binary/scripts/test4.sh")

    def test_05(self):
        self.exec_script("binary/scripts/test5.sh")

    def test_06(self):
        self.exec_script("binary/scripts/test6.sh")

    def test_07(self):
        self.exec_script("binary/scripts/test7.sh")

    def test_08(self):
        self.exec_script("binary/scripts/test8.sh")

    def test_09(self):
        self.exec_script("binary/scripts/test9.sh")

    def test_10(self):
        self.exec_script("binary/scripts/test10.sh")
