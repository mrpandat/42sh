import unittest
from cffi import FFI
from test_functions import *


class TestParser(unittest.TestCase):
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

    def test_01_index(self):
        idx = self.lib.test()
        self.assertEqual(idx, 1)

    def test_02_case_item(self):
        case_node = self.lib.init_case_node(b'mycase')
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword)')))
        self.assertFalse(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'myword')))
        self.assertFalse(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|)')))
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|myword)')))
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'myword|myword)')))
        self.assertTrue(self.lib.read_case_item(
            case_node, self.init_and_process_lexer(b'(myword|myword|myword)')))

    def test_03_rule_case(self):
        self.assertTrue(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'case myvar in\n'
                                            b'(myword1);;\n'
                                            b'(myword2)esac')))
        self.assertTrue(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'case myvar in\n'
                                            b'(myword1);;\n'
                                            b'(myword2);;esac')))
        self.assertFalse(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'cas myvar in\n'
                                            b'(myword1);;\n'
                                            b'(myword2);;esac')))
        self.assertFalse(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'case myvar in\n'
                                            b'(myword1);;\n'
                                            b'(myword2);;esc')))
        self.assertTrue(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'case myvar in\n'
                                            b'(myword1);;'
                                            b'(myword2);;esac')))
        self.assertFalse(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'case myvar in\n'
                                            b'(myword1);\n'
                                            b'(myword2);;esc')))

    def test_04_redirection(self):
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 > myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'0 > myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'2 > myword')))
        self.assertFalse(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'3 > myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 < myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >> myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 << myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 <<- myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >& myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 <& myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >| myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 <> myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1>myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1 >myword')))
        self.assertTrue(
            self.lib.read_redirection(
                self.lib.init_redirection_node(),
                self.init_and_process_lexer(b'1> myword')))
