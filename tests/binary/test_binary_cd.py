import unittest

from test_functions import *


class TestBinary_cd(unittest.TestCase):
    def test_01_noarg(self):
        self.assertEqual(execute_cmd_cmp('cd'), 0)

    def test_02_arg(self):
        a = execute_cmd("../42sh -c 'cd /home && /bin/pwd'")
        b = execute_cmd("cd /home > /dev/null && /bin/pwd")
        self.assertEqual(a.stdout == b.stdout, True)

    def test_03_cd_unexistant(self):
        self.assertEqual(execute_cmd_cmp('cd /bin/caca', True), 0)

    def test_04_cd_min(self):
        a = execute_cmd("../42sh -c 'cd /home && cd /home && cd -'")
        b = execute_cmd(
            "cd /home > /dev/null && cd /home > /dev/null && cd - > /dev/null && /bin/pwd")
        self.assertEqual((a.stdout).replace("\n", "") == (b.stdout).replace("\n", ""), True)
