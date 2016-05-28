import os
import sys
import unittest
from static.colors import bcolors

from fun import *

nb_fail = 0


class MyTestResult(unittest.TestResult):
    def addFailure(self, test, err):
        print ("--> " + bcolors.FAIL + "ERROR ", end=" ")
        print (test)
        print (str(err[1]) + bcolors.ENDC)
        global nb_fail
        nb_fail += 1

    def addSuccess(self, test):
        print ("--> " + bcolors.OKGREEN + "PASSED" + bcolors.ENDC, end=" ")
        print (test)
        unittest.TestResult.addSuccess(self, test)


def launch_test(test_name):
    print ()
    print((" Launching " + test_name + " tests ").center(80, '*'))
    print ()
    testsuite = unittest.TestLoader().discover('./' + test_name)
    unittest.TextTestRunner(verbosity=3, resultclass=MyTestResult) \
        .run(testsuite)


def launch_all():
    launch_test("binary")
    launch_test("utils")
    launch_test("lexer")
    launch_test("parser")
    launch_test("execute")


def print_nyan():
    global nb_fail
    if nb_fail == 0:
        print_colored("./static/nyan")
    else:
        print_file("./static/spider", bcolors.OKBLUE,   )


if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.realpath(__file__)))

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
