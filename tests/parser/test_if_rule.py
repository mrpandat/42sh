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

    def test_01(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_rule_if(
                node,
                self.init_and_process_lexer(b'if a then b fi')))

    def test_02(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_rule_if(
                node,
                self.init_and_process_lexer(b'if a then then b fi')))

    def test_03(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_rule_if(
                node,
                self.init_and_process_lexer(b'if if a then b fi')))

    def test_04(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_rule_if(
                node,
                self.init_and_process_lexer(b'if a then b if')))

    def test_05(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_rule_if(
                node,
                self.init_and_process_lexer(b'if a then b')))
