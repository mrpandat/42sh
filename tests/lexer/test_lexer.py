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

    def test_04_valid_if_command(self):
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

        # Check if returned token is word
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is semi
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_SEMI,
                         '[ERROR]\n\t--expected: TK_SEMI\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is then
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_THEN,
                         '[ERROR]\n\t--expected: TK_THEN\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is word
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is semi
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_SEMI,
                         '[ERROR]\n\t--expected: TK_SEMI\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is semi
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_FI,
                         '[ERROR]\n\t--expected: TK_FI\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is eof
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_EOF,
                         '[ERROR]\n\t--expected: TK_EOF\n\t --my: ' +
                         str(ctoken.type))

    def test_05_comment_matched(self):
        # Init lexer
        clexer = self.lib.lexer_init(b'echo toto # if toto; then titi; fi')
        self.assertIsNotNone(clexer, '[ERROR] Lexer is NULL')

        # Trigger lexing
        self.lib.lexer_process(clexer)

        # Check if token list is not null
        self.assertIsNotNone(clexer.tk_list, '[ERROR] Token list is NULL')

        # Check if current token is not null
        self.assertIsNotNone(clexer.tk_current, '[ERROR] Current token is NULL')

        # Check if first token type is word
        ctokentype = clexer.tk_list.type
        self.assertEqual(ctokentype, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctokentype))

        # Check if returned token is word
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is eof
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_EOF,
                         '[ERROR]\n\t--expected: TK_EOF\n\t --my: ' +
                         str(ctoken.type))

    def test_06_ionumber_matched(self):
        # Init lexer
        clexer = self.lib.lexer_init(b'echo toto 2 >& 1')
        self.assertIsNotNone(clexer, '[ERROR] Lexer is NULL')

        # Trigger lexing
        self.lib.lexer_process(clexer)

        # Check if token list is not null
        self.assertIsNotNone(clexer.tk_list, '[ERROR] Token list is NULL')

        # Check if current token is not null
        self.assertIsNotNone(clexer.tk_current, '[ERROR] Current token is NULL')

        # Check if first token type is word
        ctokentype = clexer.tk_list.type
        self.assertEqual(ctokentype, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctokentype))

        # Check if returned token is word
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is ionumber
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_IONUMBER,
                         '[ERROR]\n\t--expected: TK_IONUMBER\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is greatand
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_GREATAND,
                         '[ERROR]\n\t--expected: TK_GREATAND\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is ionumber
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_IONUMBER,
                         '[ERROR]\n\t--expected: TK_IONUMBER\n\t --my: ' +
                         str(ctoken.type))

        # Check if returned token is eof
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_EOF,
                         '[ERROR]\n\t--expected: TK_EOF\n\t --my: ' +
                         str(ctoken.type))
