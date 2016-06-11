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
                self.init_and_process_lexer(b'echo $((3 + 4))')))

    def test_02_node_attributes(self):
        node = self.lib.init_ast_node()
        self.lib.read_simple_command(
                node,
                self.init_and_process_lexer(b'echo $((3 + 4))'))
        command = node.data.s_simple_command_node
        self.assertEqual(command.nb_elements, 2)
        self.assertEqual(command.elements[0].type, self.lib.EL_WORD)
        self.assertEqual(command.elements[0].data.s_word.type, self.lib.WD_WORD)
        self.assertEqual(
            self.ffi.string(command.elements[0].data.s_word.value),
            b'echo')
        self.assertEqual(command.elements[1].type, self.lib.EL_WORD)
        self.assertEqual(command.elements[1].data.s_word.type, self.lib.WD_ARITH)
        self.assertEqual(self.ffi.string(command.elements[1].data.s_word.value), b'3+4')

    def test_03_node_attributes_hard(self):
        node = self.lib.init_ast_node()
        self.lib.read_simple_command(
            node,
            self.init_and_process_lexer(b'echo $((3 + 4  + (5 ** 2) - (3 / 4))'))
        command = node.data.s_simple_command_node
        self.assertEqual(command.nb_elements, 2)
        self.assertEqual(command.elements[0].type, self.lib.EL_WORD)
        self.assertEqual(command.elements[0].data.s_word.type, self.lib.WD_WORD)
        self.assertEqual(
            self.ffi.string(command.elements[0].data.s_word.value),
            b'echo')
        self.assertEqual(command.elements[1].type, self.lib.EL_WORD)
        self.assertEqual(command.elements[1].data.s_word.type, self.lib.WD_ARITH)
        self.assertEqual(self.ffi.string(command.elements[1].data.s_word.value), b'3+4+(5**2)-(3/4)')


