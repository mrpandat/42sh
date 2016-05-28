import unittest
from cffi import FFI
from test_functions import *


class TestParser(unittest.TestCase):
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

    def test_01_simple_do(self):
        node = self.lib.init_ast_node()
        command = b'do echo mdr done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_do_group(node, clexer))

    def test_02_simple_do(self):
        node = self.lib.init_ast_node()
        command = b'do echo mdr || echo lol done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_do_group(node, clexer))

    def test_03_no_ending_done(self):
        node = self.lib.init_ast_node()
        command = b'do echo mdr'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_do_group(node, clexer))

    def test_04_no_starting_do(self):
        node = self.lib.init_ast_node()
        command = b'echo mdr done'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_do_group(node, clexer))
