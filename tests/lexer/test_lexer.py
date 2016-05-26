import unittest
from cffi import FFI
from test_functions import *


class TestLexer(unittest.TestCase):
    def __init__(self,arg):
        unittest.TestCase.__init__(self,arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def test_01_lexer_init(self):
        # Init lexer
        clexer = self.lib.lexer_init(b'ls -l')
        self.assertIsNotNone(clexer, '[ERROR] Lexer is NULL')

        # Check if command is correct
        command = self.ffi.string(clexer.command)
        self.assertEqual(command, b'ls -l',
                         '[ERROR]\n\t--expected: ls -l\n\t--my: ' +
                         str(command))

        # Check if current is correct too
        current = self.ffi.string(clexer.current)
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

    def test_03_lexer_match_if(self):
        # Init lexer
        clexer = self.lib.lexer_init(b'if toto; then titi; fi')
        self.assertIsNotNone(clexer, '[ERROR] Lexer is NULL')

        # Trigger lexing
        self.lib.lexer_process(clexer)

        # Check if token list is not null
        self.assertIsNotNone(clexer.tk_list, '[ERROR] Token list is NULL')

        # Check if current token is not null
        self.assertIsNotNone(clexer.tk_current, '[ERROR] Current token is NULL')

        # Check if first token type is TK_IF
        ctokentype = clexer.tk_list.type
        self.assertEqual(ctokentype, self.lib.TK_IF,
                         '[ERROR]\n\t--expected: TK_IF(27)\n\t --my: ' +
                         str(ctokentype))

