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
        self.exec_script("binary/scripts/test01.sh")

    def test_02(self):
        self.exec_script("binary/scripts/test02.sh")

    def test_03(self):
        self.exec_script("binary/scripts/test03.sh")

    def test_04(self):
        self.exec_script("binary/scripts/test04.sh")

    def test_05(self):
        self.exec_script("binary/scripts/test05.sh")

    def test_06(self):
        self.exec_script("binary/scripts/test06.sh")

    def test_07(self):
        self.exec_script("binary/scripts/test07.sh")

    def test_08(self):
        self.exec_script("binary/scripts/test08.sh")

    def test_09(self):
        self.exec_script("binary/scripts/test09.sh")

