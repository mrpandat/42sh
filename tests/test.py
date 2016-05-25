from fun import print_colored
import os
import sys
import unittest
from parser.test_parser import TestParser
from lexer.test_lexer import TestLexer
from execute.test_exec import TestExec
from utils.test_utils import TestUtils


def launch_all():

    utils_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestUtils)
    parser_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestParser)
    lexer_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestLexer)
    exec_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestExec)

    print("Launching utils tests....")
    unittest.TextTestRunner().run(utils_suite)
    print("Launching parser tests....")
    unittest.TextTestRunner().run(parser_suite)
    print("Launching lexer tests....")
    unittest.TextTestRunner().run(lexer_suite)
    print("Launching execution tests....")
    unittest.TextTestRunner().run(exec_suite)
    
    os.chdir(os.path.dirname(os.path.realpath(__file__)))

if __name__ == "__main__":
    sys.argv[0] = ""
    for arg in sys.argv:
        if arg=="":
            continue
        elif arg == "-l" or arg =="--list":
            print ("categories")
            exit(0)
        elif arg == "-c":
            print("execute category")
            exit(0)
        elif arg == "-s" or arg=="--sanity":
            print ("valgrind")
            exit(0)
        else:
            print ("Unknow option : " + arg)
            exit(1)
    launch_all()




