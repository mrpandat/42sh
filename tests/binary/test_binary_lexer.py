import unittest
from test_functions import *

class TestBinaryLexer(unittest.TestCase):

    def test_1_lexer_chars_simple(self):
        result = execute_cmd('../42sh -c "/bin/echo % *+,-./0123456789=?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_abcdefghijklmnopqrstuvwxyz"')
        self.assertEqual(result.stdout, '% *+,-./0123456789=?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_abcdefghijklmnopqrstuvwxyz\n')
        self.assertEquals(result.returncode, 0)

    def test_2_lexer_chars_hard(self):
        result = execute_cmd('../42sh -c "/bin/echo \{\|\}\~\:\;\(\)\"\'"')
        self.assertEqual(result.stdout, '{|}~:;()"\'\n')
        self.assertEquals(result.returncode, 0)

    def test_3_Lexer_dot(self):
        result = execute_cmd('../42sh -c "/bin/echo ."')
        self.assertEqual(result.stdout, '.\n')
        self.assertEquals(result.returncode, 0)

    def test_4_Lexer_equals(self):
        result = execute_cmd('../42sh -c "/bin/echo ="')
        self.assertEqual(result.stdout, '=\n')
        self.assertEquals(result.returncode, 0)

