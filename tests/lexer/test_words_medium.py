import unittest

from cffi import FFI
from test_functions import *

from .utils import *


class TestWordsMedium(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def test_01_lexer_words_medium_1(self):
        init_and_process_lexer(self, b'./abcd.efg /dev/null test.out')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'./abcd.efg'),
                        (self.lib.TK_WORD, b'/dev/null'),
                        (self.lib.TK_WORD, b'test.out'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)
