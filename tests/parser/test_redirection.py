import unittest
from cffi import FFI
from test_functions import *


class TestRedirection(unittest.TestCase):
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

    def test_01_from_one(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 > myword')))

    def test_02_from_zero(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'0 > myword')))

    def test_03_from_two(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'2 > myword')))

    def test_04_from_three(self):
        self.assertFalse(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'3 > myword')))

    def test_05_to_one(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 < myword')))

    def test_06_dgreat(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >> myword')))

    def test_07_dless(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 << myword')))

    def test_09_dlessminus(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 <<- myword')))

    def test_10_greatand(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >& myword')))

    def test_11_lessand(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 <& myword')))

    def test_12_greator(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >| myword')))

    def test_13_lessgreat(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 <> myword')))

    def test_14_no_space(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1>myword')))

    def test_15_left_space(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >myword')))

    def test_16_right_space(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1> myword')))

    def test_17_ionumber_into_ionumber(self):
        self.assertFalse(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 > 2')))

    def test_18_no_ionumber(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'> myword')))

    def test_18_node_attributes(self):
        element_node = self.lib.init_element_node()
        self.lib.read_element(element_node,
                              self.init_and_process_lexer(b'1 > myword'))
        self.assertEqual(b'1',
                         self.ffi.string(
                             element_node.data.s_redirection_node.io_number))
        self.assertEqual(b'>',
                         self.ffi.string(
                             element_node.data.s_redirection_node.type))
        self.assertEqual(b'myword',
                         self.ffi.string(
                             element_node.data.s_redirection_node.word))
