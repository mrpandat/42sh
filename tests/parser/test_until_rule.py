import unittest
from cffi import FFI
from test_functions import *


class TestUntilRule(unittest.TestCase):
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

    def test_01_simple_until(self):
        node = self.lib.init_ast_node()
        command = b'until variable do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_rule_while(node, clexer))

    def test_02_until_typo(self):
        node = self.lib.init_ast_node()
        command = b'unti variable do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_rule_while(node, clexer))

    def test_03_two_ors(self):
        node = self.lib.init_ast_node()
        command = b'until variable1 || variable2 do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_rule_while(node, clexer))
