import unittest
from cffi import FFI
from test_functions import *


class TestSimpleCommand(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def init_and_process_lexer(self, command):
        clexer = self.lib.lexer_init(command)
        self.lib.lexer_process(clexer)
        return clexer

    def test_01_simple_command(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'1 > myword > myword')))

    def test_02_simple_word(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'myword')))

    def test_03_redirection(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'1 > 2 myword')))

    def test_04_redirection_double_word(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'1 > myword > myword myword')))

    def test_05_multiple_redirections(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'1 > 2 < 4 myword')))

