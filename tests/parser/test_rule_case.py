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

    def test_07_node_attributes(self):
        command = b'case myvar in\n(myword1);;\n(myword2|myword3);;esac'
        node = self.lib.init_ast_node()
        clexer = self.init_and_process_lexer(command)
        self.lib.read_rule_case(node, clexer)
        case_node = node.data.s_case_node
        self.assertEqual(2, case_node.nb_items)
        self.assertEqual(b'myvar', self.ffi.string(case_node.word))
        self.assertEqual(b'myword1',
                         self.ffi.string(case_node.items[0].words[0]))
        self.assertEqual(b'myword2',
                         self.ffi.string(case_node.items[1].words[0]))
        self.assertEqual(b'myword3',
                         self.ffi.string(case_node.items[1].words[1]))

