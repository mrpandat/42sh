import unittest

from cffi import FFI
from test_functions import *

from .utils import *


class TestLexerQuoting(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def test_01_lexer_simple_quotes_simple(self):
        init_and_process_lexer(self, b'echo \'toto\';')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'echo'),
                        (self.lib.TK_ESC_WORD, b'toto'),
                        (self.lib.TK_SEMI, b';'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)

    def test_02_lexer_double_quotes_simple(self):
        init_and_process_lexer(self, b'echo \"toto\";')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'echo'),
                        (self.lib.TK_WORD, b'toto'),
                        (self.lib.TK_SEMI, b';'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)
