import unittest
from cffi import FFI
from test_functions import *


class TestDoGroup(unittest.TestCase):
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

    def test_01_simple_do(self):
        node = self.lib.init_ast_node()
        command = b'do echo mdr done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_do_group(node, clexer))

    def test_02_simple_do(self):
        node = self.lib.init_ast_node()
        command = b'do echo mdr || echo lol done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_do_group(node, clexer))

    def test_03_no_ending_done(self):
        node = self.lib.init_ast_node()
        command = b'do echo mdr'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_do_group(node, clexer))

    def test_04_no_starting_do(self):
        node = self.lib.init_ast_node()
        command = b'echo mdr done'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_do_group(node, clexer))

    def test_05_node_attributes(self):
        node = self.lib.init_ast_node()
        command = b'do echo mdr done'
        clexer = self.init_and_process_lexer(command)
        self.lib.read_do_group(node, clexer)
        self.assertEqual(node.type, self.lib.ND_LIST)
        list_node_1 = node.data.s_list_node
        and_or_1 = list_node_1.left.data.s_and_or_node
        command_1 = and_or_1.left.data.s_pipeline_node.commands[0].data \
            .s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command_1.elements[0].data.s_word.value), b'echo')
        self.assertEqual(self.ffi.string(command_1.elements[1].data.s_word.value), b'mdr')
