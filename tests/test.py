import sys
import unittest
from static.colors import bcolors
from fun import *
from binary.test_binary import TestBinary
from execute.test_exec import TestExec
from lexer.test_lexer import TestLexer
from parser.test_parser import TestParser
from utils.test_utils import TestUtils

nb_fail = 0

class MyTestResult(unittest.TestResult):
    def addFailure(self, test, err):
        print ("--> " + bcolors.FAIL + "FAIL" + bcolors.ENDC, end=" ")
        print (test)

    def addSuccess(self, test):
        print ("--> " + bcolors.OKGREEN + "PASSED" + bcolors.ENDC, end=" ")
        print (test)


def launch_test(test, test_name):
    parser_suite = unittest.defaultTestLoader.loadTestsFromTestCase(test)
    print ()
    print((" Launching " + test_name + " tests ").center(80, '*'))
    print ()
    res = TestResult()
    parser_suite.run(res)
    print (res)
    global nb_fail
    nb_fail += len(res.errors)
    nb_fail += len(res.failures)


def launch_all():
    launch_test(TestBinary, "binary")
    launch_test(TestUtils, "utils")
    launch_test(TestLexer, "lexer")
    launch_test(TestParser, "parser")
    launch_test(TestExec, "exe")

def print_nyan():
    global nb_fail
    if nb_fail == 0:
        print_colored("./static/nyan")
    else:
        print_colored("./static/dead")

if __name__ == "__main__":
    categorie = ["utils", "lexer", "parser", "execute", "binary"]
    sys.argv[0] = ""
    for arg in sys.argv:
        if arg == "":
            continue
        elif arg == "-l" or arg == "--list":
            print (', '.join(categorie))
            exit(0)
        elif arg == "-s" or arg == "--sanity":
            print("valgrind")
        elif arg == "-c":
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
            print_nyan()
            exit(0)
        else:
            print ("Unknow option : " + arg)
            exit(1)
    launch_all()
    print_nyan()

