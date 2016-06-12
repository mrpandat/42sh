import unittest
from cffi import FFI
from test_functions import *


class TestSimpleCommand(unittest.TestCase):
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

    def test_01_simple_command(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'1 > myword > myword')))

    def test_02_simple_word(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'myword')))

    def test_03_redirection(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'1 > 2 myword')))

    def test_04_redirection_double_word(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'1 > myword > myword myword')))

    def test_05_multiple_redirections(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'1 > word < word myword')))

    def test_06_node_attributes(self):
        node = self.lib.init_ast_node()
        self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'1 > word1 < word2 word3'))
        command = node.data.s_simple_command_node
        self.assertEqual(command.nb_elements, 3)
        self.assertEqual(command.elements[0].type, self.lib.EL_REDIRECTION)
        self.assertEqual(
            self.ffi.string(
                command.elements[0].data.s_redirection_node.io_number),
            b'1')
        self.assertEqual(
            self.ffi.string(command.elements[0].data.s_redirection_node.type),
            b'>')
        self.assertEqual(
            self.ffi.string(command.elements[0].data.s_redirection_node.word),
            b'word1')
        self.assertEqual(command.elements[1].type, self.lib.EL_REDIRECTION)
        self.assertEqual(command.elements[1].data.s_redirection_node.io_number,
                         self.ffi.NULL)
        self.assertEqual(
            self.ffi.string(command.elements[1].data.s_redirection_node.type),
            b'<')
        self.assertEqual(
            self.ffi.string(command.elements[1].data.s_redirection_node.word),
            b'word2')
        self.assertEqual(command.elements[2].type, self.lib.EL_WORD)
        self.assertEqual(self.ffi.string(command.elements[2].data.s_word.value),
                         b'word3')


