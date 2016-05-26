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

    def test_01_index(self):
        idx = self.lib.test()
        self.assertEqual(idx, 1)

    def test_02_case_item(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword)')))
        self.assertFalse(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'myword')))
        self.assertFalse(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|)')))
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|myword)')))
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'myword|myword)')))
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|myword|myword)')))



