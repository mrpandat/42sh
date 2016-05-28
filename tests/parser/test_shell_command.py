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

    def test_01_pars(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_shell_command(
                node,
                self.init_and_process_lexer(b'(word1 || word2 || word3)')))

    def test_02_pars(self):
        node = self.lib.init_ast_node()
        self.assertTrue(
            self.lib.read_shell_command(
                node,
                self.init_and_process_lexer(b'{word1 || word2 || word3}')))

    def test_03_braces_and_pars(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_shell_command(
                node,
                self.init_and_process_lexer(b'{myword || myword)')))

    def test_04_braces_and_pars(self):
        node = self.lib.init_ast_node()
        self.assertFalse(
            self.lib.read_shell_command(
                node,
                self.init_and_process_lexer(b'(word1 || word2 || word3}')))

    def test_05_until(self):
        node = self.lib.init_ast_node()
        command = b'until variable do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_shell_command(node, clexer))

    def test_06_while(self):
        node = self.lib.init_ast_node()
        command = b'while variable do shit done'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_shell_command(node, clexer))

    def test_07_if(self):
        node = self.lib.init_ast_node()
        command = b'if a then b fi'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_shell_command(node, clexer))

    def test_08_case(self):
        node = self.lib.init_ast_node()
        command = b'case myvar in\n(myword1);;\n(myword2)esac'
        clexer = self.init_and_process_lexer(command)
        self.assertTrue(self.lib.read_shell_command(node, clexer))

    def test_09_wrong_case(self):
        node = self.lib.init_ast_node()
        command = b'case myvar in\n(myword1);;\n(myword2)esc'
        clexer = self.init_and_process_lexer(command)
        self.assertFalse(self.lib.read_shell_command(node, clexer))
