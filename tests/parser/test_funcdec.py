import unittest
from cffi import FFI
from test_functions import *


class TestShellCommand(unittest.TestCase):
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

    def test_01_simple_funcdec(self):
        node = self.lib.init_ast_node()
        command = b'function myword() if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_funcdec(node, clexer))

    def test_02_no_funcdec_word(self):
        node = self.lib.init_ast_node()
        command = b'myword() if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_funcdec(node, clexer))

    def test_03_no_pars(self):
        node = self.lib.init_ast_node()
        command = b'function myword if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_funcdec(node, clexer))

    def test_04_no_pars_no_funcdec_word(self):
        node = self.lib.init_ast_node()
        command = b'myword if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_funcdec(node, clexer))

    def test_05_wrong_command(self):
        node = self.lib.init_ast_node()
        command = b'function myword() if a then b'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_funcdec(node, clexer))
