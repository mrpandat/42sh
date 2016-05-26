from fun import print_colored
import os
import sys
import unittest
from static.colors import bcolors
from parser.test_parser import TestParser
from lexer.test_lexer import TestLexer
from execute.test_exec import TestExec
from utils.test_utils import TestUtils
from binary.test_binary import TestBinary

class MyTestRunner(unittest.TextTestRunner):
    def _makeResult(self):
            obj = MyTestResult()
            return obj

class MyTestResult( unittest.TestResult ):
    def addFailure(self, test, err):
        print (test)
        print (bcolors.FAIL + "FAIL" + bcolors.ENDC)
        print (bcolors.FAIL + err + bcolors.ENDC)
    def addSuccess(self, test):
        print (test)
        print (bcolors.OKGREEN + "PASSED" + bcolors.ENDC)

test_runner = MyTestRunner(verbosity=3)
# LAUNCHER OF CATEGORIE
def launch_parser_tests():
    parser_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestParser)
    print(" Launching parser tests ".center(80, '*'))
    test_runner.run(parser_suite)


def launch_lexer_tests():
    lexer_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestLexer)
    print(" Launching lexer tests ".center(80, '*'))
    test_runner.run(lexer_suite)


def launch_exec_tests():
    exec_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestExec)
    print(" Launching execution tests ".center(80, '*'))
    test_runner.run(exec_suite)


def launch_utils_tests():
    utils_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestUtils)
    print(" Launching utils tests ".center(80, '*'))
    test_runner.run(utils_suite)

def launch_binary_tests():
    utils_suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestBinary)
    print(" Launching utils tests ".center(80, '*'))
    test_runner.run(utils_suite)


def launch_all():
    launch_utils_tests()
    launch_lexer_tests()
    launch_parser_tests()
    launch_exec_tests()
    launch_binary_tests()


#MAIN TEST
if __name__ == "__main__":
    categorie = ["utils", "lexer", "parser", "execute","binary"]
    sys.argv[0] = ""
    for arg in sys.argv:
        if arg == "":
            continue
        elif arg == "-l" or arg == "--list":
            print("categories")
            print (', '.join(categorie))
            exit(0)
        elif arg == "-s" or arg=="--sanity":
            print("valgrind")
        elif arg == "-c":
            print("execute category")
            if "utils" in sys.argv:
                launch_utils_tests()
            elif "lexer" in sys.argv:
                launch_lexer_tests()
            elif "parser" in sys.argv:
                launch_parser_tests()
            elif "execute" in sys.argv:
                launch_exec_tests()
            elif "binary" in sys.argv:
                launch_exec_tests()
            exit(0)
        else:
            print ("Unknow option : " + arg)
            exit(1)
    launch_all()




