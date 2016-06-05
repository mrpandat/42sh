import unittest

from cffi import FFI

from .utils import *


class TextLexerConfig(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)

        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

        self.clexer = self.ffi.NULL

    def test_01_lex_tk_list_invalid_size(self):
        self.assertEqual(-1, self.lib.lexer_token_list_size(self.clexer))

    def test_02_lex_tk_list_zero_size(self):
        init_and_process_lexer(self, b'')
        self.assertEqual(1, self.lib.lexer_token_list_size(self.clexer))
        destroy_lexer(self)

    def test_03_lex_tk_list_positive_size_simple(self):
        init_and_process_lexer(self, b'echo toto')
        self.assertEqual(3, self.lib.lexer_token_list_size(self.clexer))
        destroy_lexer(self)

    def test_04_lex_tk_list_positive_size_medium(self):
        init_and_process_lexer(self, b'echo toto && if [ 0 -eq 0 ]; then '
                                     b'echo titi; fi')
        self.assertEqual(16, self.lib.lexer_token_list_size(self.clexer))
        destroy_lexer(self)
