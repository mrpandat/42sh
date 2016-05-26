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

    def test_01_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 > myword')))

    def test_02_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'0 > myword')))

    def test_03_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'2 > myword')))

    def test_04_redirection(self):
        self.assertFalse(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'3 > myword')))

    def test_05_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 < myword')))

    def test_06_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >> myword')))

    def test_07_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 << myword')))

    def test_08_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >> myword')))

    def test_09_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 <<- myword')))

    def test_10_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >& myword')))

    def test_11_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 <& myword')))

    def test_12_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >| myword')))

    def test_13_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 <> myword')))

    def test_14_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1>myword')))

    def test_15_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >myword')))

    def test_16_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1> myword')))
