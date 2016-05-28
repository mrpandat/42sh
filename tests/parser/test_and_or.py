import unittest
from cffi import FFI
from test_functions import *


class TestAndOr(unittest.TestCase):
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

    def test_01_simple_or(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword || myword')))

    def test_02_too_much_ors(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword ||| myword')))

    def test_03_simple_and(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword && myword')))

    def test_04_too_much_ands(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword &&& myword')))

    def test_05_multiple_ors(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword || myword || myword')))

    def test_06_or_with_no_command(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword || myword || myword ||')))
