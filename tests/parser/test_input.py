import unittest
from cffi import FFI
from test_functions import *


class TestCommand(unittest.TestCase):
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

    def test_01_simple(self):
        node = self.lib.init_ast_node()
        command = b'myword || myword'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_input(node, clexer))

    def test_02_simple_with_newline(self):
        node = self.lib.init_ast_node()
        command = b'myword || myword\n'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_input(node, clexer))

    def test_03_newline(self):
        node = self.lib.init_ast_node()
        command = b'\n'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_input(node, clexer))

    def test_04_newline(self):
        node = self.lib.init_ast_node()
        command = b''
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_input(node, clexer))

    def test_05_wrong_command(self):
        node = self.lib.init_ast_node()
        command = b'|'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_input(node, clexer))
