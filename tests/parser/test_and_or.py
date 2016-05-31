import unittest
from cffi import FFI
from test_functions import *


class TestAndOr(unittest.TestCase):
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
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword || myword')))

    def test_02_too_much_ors(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword ||| myword')))

    def test_03_simple_and(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword && myword')))

    def test_04_too_much_ands(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword &&& myword')))

    def test_05_multiple_ors(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword || myword || myword')))

    def test_06_or_with_no_command(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_and_or(
                node,
                self.init_and_process_lexer(b'myword || myword || myword ||')))

    def test_07_or_node_attributes(self):
        node = self.lib.init_ast_node()
        self.lib.read_and_or(node, self.init_and_process_lexer(b'word1 || word2'))
        and_or_1 = node.data.s_and_or_node
        command_1 = and_or_1.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(and_or_1.type, self.lib.ANDOR_OR)
        self.assertEqual(self.ffi.string(command_1.elements[0].data.word), b'word1')
        and_or_2 = node.data.s_and_or_node.right.data.s_and_or_node
        command_2 = and_or_2.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(and_or_2.type, self.lib.ANDOR_NONE)
        self.assertEqual(self.ffi.string(command_2.elements[0].data.word), b'word2')

    def test_08_and_node_attributes(self):
        node = self.lib.init_ast_node()
        self.lib.read_and_or(node, self.init_and_process_lexer(b'word1 && word2'))
        and_or_1 = node.data.s_and_or_node
        command_1 = and_or_1.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(and_or_1.type, self.lib.ANDOR_AND)
        self.assertEqual(self.ffi.string(command_1.elements[0].data.word), b'word1')
        and_or_2 = node.data.s_and_or_node.right.data.s_and_or_node
        command_2 = and_or_2.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(and_or_2.type, self.lib.ANDOR_NONE)
        self.assertEqual(self.ffi.string(command_2.elements[0].data.word), b'word2')
