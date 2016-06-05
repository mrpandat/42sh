import unittest

from cffi import FFI

from .utils import *


class TestCommandsMedium(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)

        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

        self.clexer = self.ffi.NULL

    def test_01_lexer_command_with_exec_and_exotic_files(self):
        init_and_process_lexer(self, b'./brew.sh if /dev/stdio > a.out')

        self.assertTrue(
            list_equals(self, False,
                        (self.lib.TK_WORD, b'./brew.sh'),
                        (self.lib.TK_IF, b'if'),
                        (self.lib.TK_WORD, b'/dev/stdio'),
                        (self.lib.TK_GREAT, b'>'),
                        (self.lib.TK_WORD, b'a.out'),
                        (self.lib.TK_EOF, b'EOF'))
        )

        destroy_lexer(self)
