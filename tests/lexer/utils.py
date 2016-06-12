import sys

from test_functions import *


def init_and_process_lexer(test_class, command):
    test_class.clexer = test_class.lib.lexer_init(command)
    test_class.lib.lexer_process(test_class.clexer)


def destroy_lexer(test_class):
    test_class.lib.lexer_destroy(test_class.clexer)


def list_equals(test_class, verbose_mode, *args):
    if len(args) != test_class.lib.lexer_token_list_size(test_class.clexer):
        return False

    ctoken_curr = test_class.clexer.tk_current

    # token[0]: Token type
    # token[1]: Token value

    # DEBUG
    # print('Type: ' + str(ctoken_curr.type) + ' - ' + str(token[0]))
    # print('Value: ' + str(test_class.ffi.string(ctoken_curr.value)) +
    #       ' - ' + str(token[1]))
    for token in args:

        if verbose_mode:
            print('Type: ' + str(ctoken_curr.type) + ' - ' + str(token[0]))
            print('Value: ' + str(test_class.ffi.string(ctoken_curr.value)) +
                  ' - ' + str(token[1]))

        if ctoken_curr.type != token[0] \
                or test_class.ffi.string(ctoken_curr.value) != token[1]:
            return False
        ctoken_curr = ctoken_curr.next

    return True
