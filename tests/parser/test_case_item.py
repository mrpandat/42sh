import unittest
from cffi import FFI
import os
import tests


class TestCaseItem(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = tests.test_functions.get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def test_01(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword)')))

    def test_02(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertFalse(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'myword')))

    def test_03(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertFalse(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|)')))

    def test_04(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|myword)')))

    def test_05(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'myword|myword)')))

    def test_06(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|myword|myword)')))

