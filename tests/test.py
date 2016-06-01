import os
import sys
import time
import unittest

import plotly
import plotly.graph_objs as go
import plotly.plotly as py
from fun import *
from my_test_runner import MyTestRunner
from static.colors import bcolors
from test_functions import *

nb_fail = 0
nb_success = 0
nb_errors = 0
mtimeout = 300
begin = time.time()
resume_errors = ""
resume_time_x = []
resume_time_y = []


class MyTestResult(unittest.TestResult):
    def addFailure(self, test, err):
        print("--> " + bcolors.FAIL + "FAILURE ", end=" ")
        print(test)
        print(str(err[1]) + bcolors.ENDC)
        global nb_fail
        nb_fail += 1
        global resume_errors
        resume_errors += ("--> " + bcolors.FAIL + "FAILURE on " + str(test) +
                          "\n" + bcolors.ENDC)

    def addSuccess(self, test):
        print("--> " + bcolors.OKGREEN + "PASSED" + bcolors.ENDC, end=" ")
        print(test)
        global nb_success
        nb_success += 1
        unittest.TestResult.addSuccess(self, test)

    def addError(self, test, err):
        print("--> " + bcolors.WARNING + "ERROR " + bcolors.ENDC, end=" ")
        print(test)
        print(str(err[1]) + bcolors.ENDC)
        global nb_errors
        nb_errors += 1
        unittest.TestResult.addError(self, test, err)


def launch_test(test_name):
    print()
    print()
    print((" Launching " + test_name + " tests ").center(80, '*'))
    print()
    for test in [os.path.join(test_name, fn) for fn in
                 next(os.walk(test_name))[2]]:
        if "test_" in test:
            a = time.time()
            test = test.replace("/", ".").replace(".py", "")
            print(test)
            my_test = unittest.TestLoader().loadTestsFromName(test)
            if not MyTestRunner(verbosity=3, resultclass=MyTestResult).run(
                    my_test, a, begin, mtimeout):
                print("Timeout...")
                exit(1)
            else:
                global resume_time_y
                resume_time_y.append(time.time() - a)
                global resume_time_x
                resume_time_x.append(len(resume_time_x))


def launch_sanity_test():
    print()
    print(" Launching sanity tests ".center(80, '*'))
    print()
    for file in [os.path.join("binary/scripts", fn) for fn in
                 next(os.walk("binary/scripts"))[2]]:
        if file.endswith(".sh"):
            res = execute_cmd(
                "valgrind --leak-check=full --error-exitcode=42 ../42sh " + file)
            if res.returncode != 42:
                print(
                    "--> " + bcolors.OKGREEN + "SANITY OK ON FILE " + file + bcolors.ENDC)
            else:
                print(
                    "--> " + bcolors.FAIL + "UNSAIN FILE " + file +
                    bcolors.ENDC)
                global nb_fail
                nb_fail += 1
                global resume_errors
                resume_errors += ("--> " + bcolors.FAIL + "UNSAIN FILE " +
                                  file + "\n" + bcolors.ENDC)


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
        global resume_errors

        print()
        print(" ERROR  RESUME ".center(80, '*'))
        print()
        print(resume_errors)


def tracegraph():
    a = execute_cmd("pwd")
    fig = {
        'data': [{'labels': ['Errors', 'Failures', 'Success'],
                  'values': [nb_errors, nb_fail, nb_success],
                  'type': 'pie'}],
        'layout': {'title': 'Testsuit errors report'}
    }
    os.chdir(os.path.dirname(os.path.realpath(__file__)))
    pwd = execute_cmd("pwd")
    plotly.tools.set_credentials_file(username='DemoAccount',
                                      api_key='lr1c37zw81')
    b = a.stdout.strip() + "/../doc/report"
    if not os.path.isdir(b):
        execute_cmd("mkdir " + b)
    py.image.save_as(fig, a.stdout.strip() + "/../doc/report/report_errors.png")

    trace = go.Scatter(
        x=resume_time_x,
        y=resume_time_y,
        mode='lines',
        name='lines'
    )
    fig = {
        'data': [trace],
        'layout': {'title': 'Testsuit speed report',
                   'xaxis': dict(title='Tests run'),
                   'yaxis': dict(title='Speed in seconds')
                   }
    }
    py.image.save_as(fig,
                     pwd.stdout.rstrip() + '/../doc/report/report_speed.png')
    print("Reports created in " + b)


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
            tracegraph()
            exit(0)
        else:
            print("Unknow option : " + arg)
            exit(1)
    launch_all()
    print_nyan()
    tracegraph()
