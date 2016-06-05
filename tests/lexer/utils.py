import sys

from test_functions import *


def init_and_process_lexer(test_class, command):
    test_class.clexer = test_class.lib.lexer_init(command)
    test_class.lib.lexer_process(test_class.clexer)


def destroy_lexer(test_class):
    test_class.lib.lexer_destroy(test_class.clexer)


def list_equals(test_class, *args):
    try:
        print(test_class.ffi.string(test_class.clexer.command))
    except AttributeError:
        print('No lexer instance found in %s instance.' %
              type(test_class).__name__, file=sys.stderr)
        exit()

    for lst in args:
        for count, pair in enumerate(lst):
            print(str(pair[0]) + ' -> ' + str(pair[1]))

    return True
