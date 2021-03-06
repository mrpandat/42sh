import unittest
from cffi import FFI
from test_functions import *


class TestForRule(unittest.TestCase):
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

    def test_01_simple_for(self):
        node = self.lib.init_ast_node()
        command = b'for variable do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_rule_for(node, clexer))

    def test_02_for_typo(self):
        node = self.lib.init_ast_node()
        command = b'fo variable do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_rule_for(node, clexer))

    def test_03_multiple_words_with_semi(self):
        node = self.lib.init_ast_node()
        command = b'for variable in one two; do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_rule_for(node, clexer))

    def test_04_multiple_words_no_separator(self):
        node = self.lib.init_ast_node()
        command = b'for variable in one two three\ndo shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_rule_for(node, clexer))

    def test_05_node_attributes(self):
        node = self.lib.init_ast_node()
        command = b'for variable in one two three\ndo shit done'
        clexer = self.init_and_process_lexer(command)
        self.lib.read_rule_for(node, clexer)
        self.assertEqual(node.type, self.lib.ND_FOR)
        for_node = node.data.s_for_node
        self.assertEqual(self.ffi.string(for_node.iterator), b'variable')
        self.assertEqual(for_node.nb_words, 3)
        self.assertEqual(self.ffi.string(for_node.words[0]), b'one')
        self.assertEqual(self.ffi.string(for_node.words[1]), b'two')
        self.assertEqual(self.ffi.string(for_node.words[2]), b'three')
        list_node_1 = for_node.do_group.data.s_list_node
        and_or_1 = list_node_1.left.data.s_and_or_node
        command_1 = and_or_1.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command_1.elements[0].data.s_word.value), b'shit')
