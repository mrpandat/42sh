import sys

from test_functions import *


def init_and_process_arlex(test_class, command):
    test_class.carlex = test_class.lib.arlex_init(command)
    test_class.lib.arlex_process(test_class.carlex)


def destroy_arlex(test_class):
    test_class.lib.arlex_destroy(test_class.carlex)


def arlex_list_equals(test_class, verbose_mode, *args):
    carlex_curr = test_class.carlex.altk_current

    # token[0]: Token type
    # token[1]: Token value

    # DEBUG
    # print('Type: ' + str(ctoken_curr.type) + ' - ' + str(token[0]))
    # print('Value: ' + str(test_class.ffi.string(ctoken_curr.value)) +
    #       ' - ' + str(token[1]))
    for token in args:

        if verbose_mode:
            print('Type: ' + str(carlex_curr.type) + ' - ' + str(token[0]))
            print('Value: ' + str(test_class.ffi.string(carlex_curr.value)) +
                  ' - ' + str(token[1]))

        if carlex_curr.type != token[0] \
                or test_class.ffi.string(carlex_curr.value) != token[1]:
            return False
        carlex_curr = carlex_curr.next

    return True
