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
            list_equals(self,
                        (self.lib.TK_WORD, b'echo'),
                        (self.lib.TK_WORD, b'test'))
        )

        destroy_lexer(self)
