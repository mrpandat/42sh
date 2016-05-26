from fun import print_colored
import os
import sys
import unittest
from parser.test_parser import TestParser
from lexer.test_lexer import TestLexer
from execute.test_exec import TestExec
from utils.test_utils import TestUtils


def launch_parser_tests():
    parser_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestParser)
    print(" Launching parser tests ".center(80, '*'))
    unittest.TextTestRunner().run(parser_suite)


def launch_lexer_tests():
    lexer_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestLexer)
    print(" Launching lexer tests ".center(80, '*'))
    unittest.TextTestRunner().run(lexer_suite)


def launch_exec_tests():
    exec_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestExec)
    print(" Launching execution tests ".center(80, '*'))
    unittest.TextTestRunner().run(exec_suite)


def launch_utils_tests():
    utils_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestUtils)
    print(" Launching utils tests ".center(80, '*'))
    unittest.TextTestRunner().run(utils_suite)


def launch_all():
    launch_utils_tests()
    launch_lexer_tests()
    launch_parser_tests()
    launch_exec_tests()


if __name__ == "__main__":
    sys.argv[0] = ""
    for arg in sys.argv:
        if arg == "":
            continue
        elif arg == "-l" or arg == "--list":
            print("categories")
            exit(0)
        elif arg == "-c":
            print("execute category")
            exit(0)
        elif arg == "-s" or arg=="--sanity":
            print("valgrind")
            exit(0)
    if any(["utils", "lexer", "parser", "execute"]) in sys.argv:
        if "utils" in sys.argv:
            launch_utils_tests()
        if "lexer" in sys.argv:
            launch_lexer_tests()
        if "parser" in sys.argv:
            launch_parser_tests()
        if "execute" in sys.argv:
            launch_exec_tests()
    else:
        launch_all()




