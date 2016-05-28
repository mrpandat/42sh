import unittest
from cffi import FFI
from test_functions import *


class TestRuleCase(unittest.TestCase):
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

    def test_01_simple_case(self):
        self.assertTrue(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'case myvar in\n'
                                            b'(myword1);;\n'
                                            b'(myword2)esac')))

    def test_02_ending_dsemi(self):
        self.assertTrue(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'case myvar in\n'
                                            b'(myword1);;\n'
                                            b'(myword2);;esac')))

    def test_03_case_typo(self):
        self.assertFalse(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'cas myvar in\n'
                                            b'(myword1);;\n'
                                            b'(myword2);;esac')))

    def test_04_esac_typo(self):
        self.assertFalse(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'case myvar in\n'
                                            b'(myword1);;\n'
                                            b'(myword2);;esc')))

    def test_05_no_newline(self):
        self.assertTrue(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'case myvar in\n'
                                            b'(myword1);;'
                                            b'(myword2);;esac')))

    def test_06_simple_semi(self):
        self.assertFalse(
            self.lib.read_rule_case(
                self.lib.init_ast_node(),
                self.init_and_process_lexer(b'case myvar in\n'
                                            b'(myword1);\n'
                                            b'(myword2);;esac')))
