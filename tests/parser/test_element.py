import unittest
from cffi import FFI
from test_functions import *


class TestElement(unittest.TestCase):
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

    def test_01_simple_word(self):
        element_node = self.lib.init_element_node()
        self.assertTrue(self.lib.read_element(
            element_node, self.init_and_process_lexer(b'myword')))

    def test_02_redirection_and_word(self):
        element_node = self.lib.init_element_node()
        self.assertTrue(self.lib.read_element(
            element_node, self.init_and_process_lexer(b'1 > myword')))

    def test_03_word_with_pars(self):
        element_node = self.lib.init_element_node()
        self.assertFalse(self.lib.read_element(
            element_node, self.init_and_process_lexer(b'(myword)')))
