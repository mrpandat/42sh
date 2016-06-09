import unittest
from cffi import FFI
from test_functions import *


class TestShellCommand(unittest.TestCase):
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

    def test_01_simple_funcdec(self):
        node = self.lib.init_ast_node()
        command = b'function myword() if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_funcdec(node, clexer))

    def test_02_no_funcdec_word(self):
        node = self.lib.init_ast_node()
        command = b'myword() if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_funcdec(node, clexer))

    def test_03_no_pars(self):
        node = self.lib.init_ast_node()
        command = b'function myword if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_funcdec(node, clexer))

    def test_04_no_pars_no_function_word(self):
        node = self.lib.init_ast_node()
        command = b'myword() if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_funcdec(node, clexer))

    def test_05_wrong_command(self):
        node = self.lib.init_ast_node()
        command = b'function myword() if a then b'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_funcdec(node, clexer))

    def test_06_simple_funcdec(self):
        node = self.lib.init_ast_node()
        command = b'function myfunction() if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.lib.read_funcdec(node, clexer)
        funcdec = node.data.s_funcdec_node
        self.assertEqual(self.ffi.string(funcdec.name), b'myfunction')
        if_node = funcdec.shell_command.data.s_if_node
        list_node_1 = if_node.predicate.data.s_list_node
        and_or_1 = list_node_1.left.data.s_and_or_node
        command_1 = and_or_1.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command_1.elements[0].data.s_word.value), b'a')
        list_node_2 = if_node.true_statement.data.s_list_node
        and_or_2 = list_node_2.left.data.s_and_or_node
        command_2 = and_or_2.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command_2.elements[0].data.s_word.value), b'b')
        self.assertEqual(if_node.false_statement, self.ffi.NULL)


