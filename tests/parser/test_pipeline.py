import unittest
from cffi import FFI
from test_functions import *


class TestPipeline(unittest.TestCase):
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

    def test_01_simple_word(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_pipeline(
                node,
                self.init_and_process_lexer(b'myword')))

    def test_02_pipe_with_newlines(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_pipeline(
                node,
                self.init_and_process_lexer(b'myword |\n\n myword')))

    def test_03_banged_no_space(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_pipeline(
                node,
                self.init_and_process_lexer(b'!myword | myword')))

    def test_04_spaced_bang(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_pipeline(
                node,
                self.init_and_process_lexer(b'! myword | myword')))

    def test_05_double_pipe_with_no_command(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_pipeline(
                node,
                self.init_and_process_lexer(b'myword | | myword')))

    def test_06_node_attributes(self):
        node = self.lib.init_ast_node()
        self.lib.read_pipeline(
            node,
            self.init_and_process_lexer(b'! word1 | word2'))
        pipe = node.data.s_pipeline_node
        self.assertTrue(pipe.banged)
        self.assertEqual(pipe.nb_commands, 2)
        command1 = pipe.commands[0].data.s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command1.elements[0].data.s_word.value),
                         b'word1')
        command2 = pipe.commands[1].data.s_command_node.content.data.s_simple_command_node
        self.assertEqual(self.ffi.string(command2.elements[0].data.s_word.value),
                         b'word2')
