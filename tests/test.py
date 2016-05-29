import os
import sys
import unittest
import time

from my_test_runner import MyTestRunner
from static.colors import bcolors
from fun import *
from test_functions import *

nb_fail = 0
mtimeout = 300
begin = time.time()

class MyTestResult(unittest.TestResult):
    def addFailure(self, test, err):
        print("--> " + bcolors.FAIL + "FAILURE ", end=" ")
        print(test)
        print(str(err[1]) + bcolors.ENDC)
        global nb_fail
        nb_fail += 1

    def addSuccess(self, test):
        print("--> " + bcolors.OKGREEN + "PASSED" + bcolors.ENDC, end=" ")
        print(test)
        unittest.TestResult.addSuccess(self, test)

    def addError(self, test, err):
        print("--> " + bcolors.WARNING + "ERROR " + bcolors.ENDC, end=" ")
        print(test)
        print(str(err[1]) + bcolors.ENDC)
        global nb_fail
        nb_fail += 1
        unittest.TestResult.addError(self, test, err)


def launch_test(test_name):
    print()
    print()
    print((" Launching " + test_name + " tests ").center(80, '*'))
    print()
    # test_suite = unittest.TestLoader().discover('./' + test_name)
    # MyTestRunner(verbosity=3, resultclass=MyTestResult).run(test_suite, a)
    for test in [os.path.join(test_name, fn) for fn in next(os.walk(test_name))[2]]:
        if "test_" in test:
            a = time.time()
            test = test.replace("/", ".").replace(".py", "")
            print(test)
            my_test = unittest.TestLoader().loadTestsFromName(test)
            if not MyTestRunner(verbosity=3, resultclass=MyTestResult).run(my_test, a,begin, mtimeout):
                print("Timeout...")
                exit(1)


def launch_sanity_test():
    print()
    print(" Launching sanity tests ".center(80, '*'))
    print()
    for file in [os.path.join("binary/scripts", fn) for fn in next(os.walk("binary/scripts"))[2]]:
        if file.endswith(".sh"):
            res = execute_cmd("valgrind ../42sh " + file)

            if "All heap blocks were freed -- no leaks are possible" in res.stderr:
                print("--> " + bcolors.OKGREEN + "SANITY OK ON FILE " + file + bcolors.ENDC)
            else:
                print("--> " + bcolors.FAIL + "INSAIN FILE " + file + bcolors.ENDC)
                global nb_fail
                nb_fail += 1


def launch_all():
    launch_test("binary")
    launch_test("utils")
    launch_test("lexer")
    launch_test("parser")
    launch_test("execute")
    launch_sanity_test()


def print_nyan():
    global nb_fail
    if nb_fail == 0:
        print_colored("./static/nyan")
    else:
        print_file("./static/spider", bcolors.OKBLUE)


if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.realpath(__file__)))

    categorie = ["utils", "lexer", "parser", "execute", "binary"]
    sys.argv[0] = ""
    loop = enumerate(sys.argv)
    skip = False
    for id, arg in loop:
        if skip:
            skip = False
            continue
        if arg == "":
            continue
        if arg == "-l" or arg == "--list":
            print(', '.join(categorie))
            exit(0)
        elif arg == "-t" or arg == "--timeout":
            if len(sys.argv) < id + 1:
                print("Missing operator after " + arg)
                exit(1)
            try:
                mtimeout = float(sys.argv[id + 1])
            except ValueError:
                print("Error: " + sys.argv[id + 1] + " is not a number")
                exit(1)
            skip = True
            continue
        elif arg == "-s" or arg == "--sanity":
            launch_sanity_test()
            print_nyan()
            exit(0)
        elif arg == "-c":
            if "utils" in sys.argv:
                launch_test("utils")
            elif "lexer" in sys.argv:
                launch_test("lexer")
            elif "parser" in sys.argv:
                launch_test("parser")
            elif "execute" in sys.argv:
                launch_test("execute")
            elif "binary" in sys.argv:
                launch_test("binary")
            print_nyan()
            exit(0)
        else:
            print("Unknow option : " + arg)
            exit(1)
    launch_all()
    print_nyan()
