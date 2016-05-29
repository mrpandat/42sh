import unittest
from cffi import FFI
from test_functions import *


class TestCommand(unittest.TestCase):
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

    def test_01_funcdec(self):
        node = self.lib.init_ast_node()
        command = b'myword() if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_command(node, clexer))

    def test_02_funcdec_and_redirection(self):
        node = self.lib.init_ast_node()
        command = b'myword() if a then b fi > file'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_command(node, clexer))

    def test_03_simple_command(self):
        node = self.lib.init_ast_node()
        command = b'1 > myword > myword'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_command(node, clexer))

    def test_04_shell_command(self):
        node = self.lib.init_ast_node()
        command = b'while variable do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_command(node, clexer))

    def test_05_shell_command_and_redirection(self):
        node = self.lib.init_ast_node()
        command = b'while variable do shit done > file'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_command(node, clexer))

    def test_06_wrong_command(self):
        node = self.lib.init_ast_node()
        command = b'while variable do shit don'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_command(node, clexer))

    def test_07_node_attributes(self):
        node = self.lib.init_ast_node()
        command = b'myfunction() if a then b fi > output'
        clexer = self.init_and_process_lexer(command)
        self.lib.read_command(node, clexer)
        command = node.data.s_command_node
        funcdec = command.content.data.s_funcdec_node
        self.assertEqual(self.ffi.string(funcdec.name), b'myfunction')
        self.assertEqual(command.nb_redirections, 1)
        redirection = command.redirections[0]
        self.assertEqual(redirection.io_number, self.ffi.NULL)
        self.assertEqual(self.ffi.string(redirection.type), b'>')
        self.assertEqual(self.ffi.string(redirection.word), b'output')
