import unittest

from cffi import FFI

from .utils import *


class TestCommandsEasy(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)

        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

        self.clexer = self.ffi.NULL

    def test_01_lex_simple_echo(self):
        init_and_process_lexer(self, b'echo test')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'echo'),
                        (self.lib.TK_WORD, b'test'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)

    def test_02_lex_simple_and_op(self):
        init_and_process_lexer(self, b'echo test && cat -e toto.txt')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'echo'),
                        (self.lib.TK_WORD, b'test'),
                        (self.lib.TK_AND_IF, b'&&'),
                        (self.lib.TK_WORD, b'cat'),
                        (self.lib.TK_WORD, b'-e'),
                        (self.lib.TK_WORD, b'toto.txt'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)

    def test_03_lex_simple_or_op(self):
        init_and_process_lexer(self, b'test -e AUTHORS || echo File not found.')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'test'),
                        (self.lib.TK_WORD, b'-e'),
                        (self.lib.TK_WORD, b'AUTHORS'),
                        (self.lib.TK_OR_IF, b'||'),
                        (self.lib.TK_WORD, b'echo'),
                        (self.lib.TK_WORD, b'File'),
                        (self.lib.TK_WORD, b'not'),
                        (self.lib.TK_WORD, b'found.'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)

    def test_04_lex_simple_newline(self):
        init_and_process_lexer(self, b'cat TODO\n')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'cat'),
                        (self.lib.TK_WORD, b'TODO'),
                        (self.lib.TK_NEWLINE, b'\n'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)
