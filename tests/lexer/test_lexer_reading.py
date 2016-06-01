import unittest
from cffi import FFI
from test_functions import *


class TestLexerReading(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def test_01_lexer_read_words_simple(self):
        # Init lexer
        clexer = self.lib.lexer_init(b'je suis thomas et je suis un _homme')
        self.assertIsNotNone(clexer, '[ERROR] Lexer is NULL')

        self.lib.lexer_read_word(clexer)
        clexer.current += 1
        self.lib.lexer_read_word(clexer)
        clexer.current += 1
        self.lib.lexer_read_word(clexer)
        clexer.current += 1
        self.lib.lexer_read_word(clexer)
        clexer.current += 1
        self.lib.lexer_read_word(clexer)
        clexer.current += 1
        self.lib.lexer_read_word(clexer)
        clexer.current += 1
        self.lib.lexer_read_word(clexer)
        clexer.current += 1
        self.lib.lexer_read_word(clexer)

        # Reset list
        clexer.tk_current = clexer.tk_list

        # Check first token
        ctoken = self.lib.lexer_peek(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        self.assertEqual(self.ffi.string(ctoken.value), b'je',
                         '[ERROR]\n\t--expected: je\n\t --my: ' +
                         str(self.ffi.string(ctoken.value)))

        # Check next tokens
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        self.assertEqual(self.ffi.string(ctoken.value), b'suis',
                         '[ERROR]\n\t--expected: suis\n\t --my: ' +
                         str(self.ffi.string(ctoken.value)))

        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        self.assertEqual(self.ffi.string(ctoken.value), b'thomas',
                         '[ERROR]\n\t--expected: thomas\n\t --my: ' +
                         str(self.ffi.string(ctoken.value)))

    def test_02_lexer_read_words_hard(self):
        # Init lexer
        clexer = self.lib.lexer_init(b'./abcd.efg /dev/null test.out')
        self.assertIsNotNone(clexer, '[ERROR] Lexer is NULL')

        self.lib.lexer_read_word(clexer)
        clexer.current += 1
        self.lib.lexer_read_word(clexer)
        clexer.current += 1
        self.lib.lexer_read_word(clexer)

        # Reset list
        clexer.tk_current = clexer.tk_list

        # Check first token
        ctoken = self.lib.lexer_peek(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        self.assertEqual(self.ffi.string(ctoken.value), b'./abcd.efg',
                         '[ERROR]\n\t--expected: ./abcd.efg\n\t --my: ' +
                         str(self.ffi.string(ctoken.value)))

        # Check next tokens
        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        self.assertEqual(self.ffi.string(ctoken.value), b'/dev/null',
                         '[ERROR]\n\t--expected: /dev/null\n\t --my: ' +
                         str(self.ffi.string(ctoken.value)))

        ctoken = self.lib.lexer_read(clexer)
        self.assertEqual(ctoken.type, self.lib.TK_WORD,
                         '[ERROR]\n\t--expected: TK_WORD\n\t --my: ' +
                         str(ctoken.type))

        self.assertEqual(self.ffi.string(ctoken.value), b'test.out',
                         '[ERROR]\n\t--expected: test.out\n\t --my: ' +
                         str(self.ffi.string(ctoken.value)))
