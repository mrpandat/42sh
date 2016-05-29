import unittest
from cffi import FFI
import os
from test_functions import *


class TestCaseItem(unittest.TestCase):
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

    def test_01_item_with_pars(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword)')))

    def test_02_item_with_no_pars(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertFalse(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'myword')))

    def test_03_or_with_no_command(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertFalse(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|)')))

    def test_04_simple_item(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|myword)')))

    def test_05_no_starting_par(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'myword|myword)')))

    def test_06_multiple_ors(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|myword|myword)')))

    def test_07_node_words(self):
        command = b'(word1|word2|word3) myword || myword & myword'
        case_node = self.lib.init_case_node(b'mycase')
        self.lib.read_case_item(case_node, self.init_and_process_lexer(command))
        self.assertEqual(b'word1', self.ffi.string(case_node.items[0].words[0]))
        self.assertEqual(b'word2', self.ffi.string(case_node.items[0].words[1]))
        self.assertEqual(b'word3', self.ffi.string(case_node.items[0].words[2]))

