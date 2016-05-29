import unittest
from cffi import FFI
from test_functions import *


class TestLexerQuoting(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def test_01_lexer_simple_quoting(self):
        # Init lexer
        clexer = self.lib.lexer_init(b'echo \'toto\';')
        self.assertIsNotNone(clexer, '[ERROR] Lexer is NULL')

        # Trigger lexing
        self.lib.lexer_process(clexer)

        # Check if token list is not null
        self.assertIsNotNone(clexer.tk_list, '[ERROR] Token list is NULL')

        # Check if current token is not null
        self.assertIsNotNone(clexer.tk_current, '[ERROR] Current token is NULL')

        # Check if first token type is TK_WORD
        ctokentype = clexer.tk_list.type
        self.assertEqual(ctokentype, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_IF(27)\n\t --my: ' +
                         str(ctokentype))

        # Check if returned token is word
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_ESC_WORD,
                         '[ERROR]\n\t--expected: TK_ESC_WORD\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is semicolon
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_SEMI,
                         '[ERROR]\n\t--expected: TK_SEMI\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is end of file
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_EOF,
                         '[ERROR]\n\t--expected: TK_EOF\n\t --my: ' +
                         str(ctoken.type))

    def test_02_lexer_simple_dquoting(self):
        # Init lexer
        clexer = self.lib.lexer_init(b'echo \"toto\";')
        self.assertIsNotNone(clexer, '[ERROR] Lexer is NULL')

        # Trigger lexing
        self.lib.lexer_process(clexer)

        # Check if token list is not null
        self.assertIsNotNone(clexer.tk_list, '[ERROR] Token list is NULL')

        # Check if current token is not null
        self.assertIsNotNone(clexer.tk_current, '[ERROR] Current token is NULL')

        # Check if first token type is TK_WORD
        ctokentype = clexer.tk_list.type
        self.assertEqual(ctokentype, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_IF(27)\n\t --my: ' +
                         str(ctokentype))

        # Check if returned token is word
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is semicolon
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_SEMI,
                         '[ERROR]\n\t--expected: TK_SEMI\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is end of file
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_EOF,
                         '[ERROR]\n\t--expected: TK_EOF\n\t --my: ' +
                         str(ctoken.type))
