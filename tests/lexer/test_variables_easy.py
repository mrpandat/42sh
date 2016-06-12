import unittest

from cffi import FFI

from .utils import *


class TestVariablesEasy(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)

        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

        self.clexer = self.ffi.NULL

    def test_01_lexer_simple_ionumber(self):
        init_and_process_lexer(self, b'echo toto 2 >& 1')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'echo'),
                        (self.lib.TK_WORD, b'toto'),
                        (self.lib.TK_IONUMBER, b'2'),
                        (self.lib.TK_GREATAND, b'>&'),
                        (self.lib.TK_IONUMBER, b'1'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)

    def test_02_lexer_invalid_ionumber_simple(self):
        init_and_process_lexer(self, b'echo titi 3 >& 2')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'echo'),
                        (self.lib.TK_WORD, b'titi'),
                        (self.lib.TK_WORD, b'3'),
                        (self.lib.TK_GREATAND, b'>&'),
                        (self.lib.TK_IONUMBER, b'2'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)
