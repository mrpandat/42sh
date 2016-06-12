import unittest

from cffi import FFI
from test_functions import *

from .utils import *


class TestWordsEasy(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def test_01_lexer_words_simple_1(self):
        init_and_process_lexer(self, b'je suis thomas et je suis un _homme')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'je'),
                        (self.lib.TK_WORD, b'suis'),
                        (self.lib.TK_WORD, b'thomas'),
                        (self.lib.TK_WORD, b'et'),
                        (self.lib.TK_WORD, b'je'),
                        (self.lib.TK_WORD, b'suis'),
                        (self.lib.TK_WORD, b'un'),
                        (self.lib.TK_WORD, b'_homme'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)
