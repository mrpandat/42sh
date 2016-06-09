import unittest
from cffi import FFI
from test_functions import *


class TestCompoundList(unittest.TestCase):
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
            self.lib.read_compound_list(
                node,
                self.init_and_process_lexer(b'myword || myword')))

    def test_02_ending_semi(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_compound_list(
                node,
                self.init_and_process_lexer(b'myword || myword;')))

    def test_03_and_plus_or(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_compound_list(
                node,
                self.init_and_process_lexer(b'myword || myword & myword')))

    def test_04_with_newlines(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_compound_list(
                node,
                self.init_and_process_lexer(b'myword || myword \n myword')))

    def test_05_simple_word(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_compound_list(
                node,
                self.init_and_process_lexer(b'myword')))

    def test_06_or_node_attributes(self):
        node = self.lib.init_ast_node()
        self.lib.read_compound_list(node, self.init_and_process_lexer(b'word1; word2'))
        list_node_1 = node.data.s_list_node
        and_or_1 = list_node_1.left.data.s_and_or_node
        command_1 = and_or_1.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(list_node_1.type, self.lib.LIST_SEMI)
        self.assertEqual(self.ffi.string(command_1.elements[0].data.s_word.value), b'word1')
        list_node_2 = list_node_1.right.data.s_list_node
        and_or_2 = list_node_2.left.data.s_and_or_node
        command_2 = and_or_2.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(list_node_2.type, self.lib.LIST_NONE)
        self.assertEqual(self.ffi.string(command_2.elements[0].data.s_word.value), b'word2')

    def test_07_and_node_attributes(self):
        node = self.lib.init_ast_node()
        self.lib.read_compound_list(node, self.init_and_process_lexer(b'word1 & word2'))
        list_node_1 = node.data.s_list_node
        and_or_1 = list_node_1.left.data.s_and_or_node
        command_1 = and_or_1.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(list_node_1.type, self.lib.LIST_AND)
        self.assertEqual(self.ffi.string(command_1.elements[0].data.s_word.value), b'word1')
        list_node_2 = list_node_1.right.data.s_list_node
        and_or_2 = list_node_2.left.data.s_and_or_node
        command_2 = and_or_2.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(list_node_2.type, self.lib.LIST_NONE)
        self.assertEqual(self.ffi.string(command_2.elements[0].data.s_word.value), b'word2')
