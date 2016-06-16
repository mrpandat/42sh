import unittest

from cffi import FFI

from .utils import *


class TestVariablesMedium(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)

        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

        self.clexer = self.ffi.NULL

    def test_01_lexer_not_simple_variable(self):
        init_and_process_lexer(self, b'echo $')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'echo'),
                        (self.lib.TK_WORD, b'$'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)
