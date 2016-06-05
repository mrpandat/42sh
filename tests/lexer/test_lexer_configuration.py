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

    def test_01_lexer_init(self):
        # Init lexer
        self.clexer = self.lib.lexer_init(b'ls -l')
        self.assertIsNotNone(self.clexer, '[ERROR] Lexer is NULL')

        # Check if command is correct
        command = self.ffi.string(self.clexer.command)
        self.assertEqual(command, b'ls -l',
                         '[ERROR]\n\t--expected: ls -l\n\t--my: ' +
                         str(command))

        # Check if current is correct too
        current = self.ffi.string(self.clexer.current)
        self.assertEqual(current, b'ls -l',
                         '[ERROR]\n\t--expected: ls -l\n\t--my: ' +
                         str(current))

    def test_02_lexer_process_launched(self):
        # Init lexer
        clexer = self.lib.lexer_init(b'if toto; then titi; fi')
        self.assertIsNotNone(clexer, '[ERROR] Lexer is NULL')

        # Trigger lexing
        self.lib.lexer_process(clexer)

        # Check if token list is not null
        self.assertIsNotNone(clexer.tk_list, '[ERROR] Token list is NULL')

        # Check if current token is not null
        self.assertIsNotNone(clexer.tk_current, '[ERROR] Current token is NULL')

    def test_03_lex_tk_list_invalid_size(self):
        self.assertEqual(-1, self.lib.lexer_token_list_size(self.clexer))

    def test_04_lex_tk_list_zero_size(self):
        init_and_process_lexer(self, b'')
        self.assertEqual(1, self.lib.lexer_token_list_size(self.clexer))
        destroy_lexer(self)

    def test_05_lex_tk_list_positive_size_simple(self):
        init_and_process_lexer(self, b'echo toto')
        self.assertEqual(3, self.lib.lexer_token_list_size(self.clexer))
        destroy_lexer(self)

    def test_06_lex_tk_list_positive_size_medium(self):
        init_and_process_lexer(self, b'echo toto && if [ 0 -eq 0 ]; then '
                                     b'echo titi; fi')
        self.assertEqual(16, self.lib.lexer_token_list_size(self.clexer))
        destroy_lexer(self)
