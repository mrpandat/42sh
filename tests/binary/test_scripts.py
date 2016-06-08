import unittest
import os
from test_functions import *


class TestBinary(unittest.TestCase):
    def test_01(self):
        self.assertEqual(execute_cmd_cmp("../42sh ../tests/binary/scripts/test1.sh"), 0)

    def test_02(self):
        self.assertEqual(execute_cmd_cmp("../42sh ../tests/binary/scripts/test2.sh"), 0)

    def test_03(self):
        self.assertEqual(execute_cmd_cmp("../42sh ../tests/binary/scripts/test3.sh"), 0)

    def test_04(self):
        self.assertEqual(execute_cmd_cmp("../42sh ../tests/binary/scripts/test4.sh"), 0)

    def test_05(self):
        self.assertEqual(execute_cmd_cmp("../42sh ../tests/binary/scripts/test5.sh"), 0)

    def test_06(self):
        self.assertEqual(execute_cmd_cmp("../42sh ../tests/binary/scripts/test6.sh"), 0)

    def test_07(self):
        self.assertEqual(execute_cmd_cmp("../42sh ../tests/binary/scripts/test7.sh"), 0)

    def test_08(self):
        self.assertEqual(execute_cmd_cmp("../42sh ../tests/binary/scripts/test8.sh"), 0)

    def test_09(self):
        self.assertEqual(execute_cmd_cmp("../42sh ../tests/binary/scripts/test9.sh"), 0)

    def test_10(self):
        self.assertEqual(execute_cmd_cmp("../42sh ../tests/binary/scripts/test10.sh"), 0)
