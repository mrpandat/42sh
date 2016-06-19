import unittest

from cffi import FFI

from .utils import *


class TextArithLexerConfig(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)

        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

        self.carlex = self.ffi.NULL

    def test_01_arlex_init(self):
        # Init lexer
        self.carlex = self.lib.arlex_init(b'2 + 3')
        self.assertIsNotNone(self.carlex, '[ERROR] Arlex is NULL')

        # Check if command is correct
        expr = self.ffi.string(self.carlex.expression)
        self.assertEqual(expr, b'2 + 3',
                         '[ERROR]\n\t--expected: 2 + 3\n\t--my: ' +
                         str(expr))

        # Check if current is correct too
        current = self.ffi.string(self.carlex.current)
        self.assertEqual(current, b'2 + 3',
                         '[ERROR]\n\t--expected: 2 + 3\n\t--my: ' +
                         str(current))

    def test_02_arlex_process_launched(self):
        # Init lexer
        self.carlex = self.lib.arlex_init(b'2 + 5 + 6')
        self.assertIsNotNone(self.carlex, '[ERROR] Arlex is NULL')

        # Trigger lexing
        self.lib.arlex_process(self.carlex)

        # Check if token list is not null
        self.assertIsNotNone(self.carlex.altk_list,
                             '[ERROR] Arlex token list is NULL')

        # Check if current token is not null
        self.assertIsNotNone(self.carlex.altk_current,
                             '[ERROR] Arlex current token is NULL')
