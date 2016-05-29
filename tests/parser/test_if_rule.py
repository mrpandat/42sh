import unittest
from cffi import FFI
from test_functions import *


class TestIfRule(unittest.TestCase):
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

    def test_01_simple_if(self):
        node = self.lib.init_ast_node()
        command = b'if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_rule_if(node, clexer))

    def test_02_two_thens(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_rule_if(
                node,
                self.init_and_process_lexer(b'if a then then b fi')))

    def test_03_two_ifs(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_rule_if(
                node,
                self.init_and_process_lexer(b'if if a then b fi')))

    def test_04_ending_if(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_rule_if(
                node,
                self.init_and_process_lexer(b'if a then b if')))

    def test_05_no_ending_fi(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_rule_if(
                node,
                self.init_and_process_lexer(b'if a then b')))

    def test_06_simple_if_else(self):
        node = self.lib.init_ast_node()
        command = b'if a then b else c fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_rule_if(node, clexer))

    def test_07_two_else(self):
        node = self.lib.init_ast_node()
        command = b'if a then b else else c fi'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_rule_if(node, clexer))

    def test_08_if_then_else_node_attributes(self):
        node = self.lib.init_ast_node()
        command = b'if a then b else c fi'
        clexer = self.init_and_process_lexer(command)
        self.lib.read_rule_if(node, clexer)
        if_node = node.data.s_if_node
        list_node_1 = if_node.predicate.data.s_list_node
        and_or_1 = list_node_1.left.data.s_and_or_node
        command_1 = and_or_1.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command_1.elements[0].data.word), b'a')
        list_node_2 = if_node.true_statement.data.s_list_node
        and_or_2 = list_node_2.left.data.s_and_or_node
        command_2 = and_or_2.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command_2.elements[0].data.word), b'b')
        list_node_3 = if_node.false_statement.data.s_list_node
        and_or_3 = list_node_3.left.data.s_and_or_node
        command_3 = and_or_3.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command_3.elements[0].data.word), b'c')

    def test_09_if_then_node_attributes(self):
        node = self.lib.init_ast_node()
        command = b'if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.lib.read_rule_if(node, clexer)
        if_node = node.data.s_if_node
        list_node_1 = if_node.predicate.data.s_list_node
        and_or_1 = list_node_1.left.data.s_and_or_node
        command_1 = and_or_1.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command_1.elements[0].data.word), b'a')
        list_node_2 = if_node.true_statement.data.s_list_node
        and_or_2 = list_node_2.left.data.s_and_or_node
        command_2 = and_or_2.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command_2.elements[0].data.word), b'b')
        self.assertEqual(if_node.false_statement, self.ffi.NULL)

