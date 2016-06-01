import unittest
from cffi import FFI
from test_functions import *


class TestWhileRule(unittest.TestCase):
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

    def test_01_simple_while(self):
        node = self.lib.init_ast_node()
        command = b'while variable do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_rule_while(node, clexer))

    def test_02_while_typo(self):
        node = self.lib.init_ast_node()
        command = b'whil variable do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_rule_while(node, clexer))

    def test_03_two_ors(self):
        node = self.lib.init_ast_node()
        command = b'while var1 || var2 do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_rule_while(node, clexer))

    def test_04_node_attributes(self):
        node = self.lib.init_ast_node()
        command = b'while variable do shit done'
        clexer = self.init_and_process_lexer(command)
        self.lib.read_rule_while(node, clexer)
        self.assertEqual(node.type, self.lib.ND_WHILE)
        while_node = node.data.s_while_node
        predicate_list_node = while_node.predicate.data.s_list_node
        predicate_and_or = predicate_list_node.left.data.s_and_or_node
        predicate_command = predicate_and_or.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(predicate_command.elements[0].data.word), b'variable')
        statement_list_node = while_node.statement.data.s_list_node
        statement_and_or = statement_list_node.left.data.s_and_or_node
        statement_command = statement_and_or.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(statement_command.elements[0].data.word), b'shit')
