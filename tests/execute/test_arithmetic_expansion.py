import unittest
from cffi import FFI
from test_functions import *


class TestExec(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

    def arith(self, expression, expected):
        self.assertEqual(self.ffi.string(self.lib.arithmetic_expansion(expression)), expected)

    def arith_bash(self, expression):
        my_result = self.ffi.string(self.lib.arithmetic_expansion(expression.encode('utf-8')))
        bash_result = execute_cmd("echo $(({}))".format(expression)).stdout.strip('\n').encode('utf-8')
        self.assertEqual(my_result, bash_result)

    def test_01_add(self):
        self.arith_bash('1 + 2')
        self.arith_bash('-10 + -10')
        self.arith_bash('99999 + 1')
        self.arith_bash('10 + -20')
        self.arith_bash('1 + 0')
        self.arith_bash('1 + 2')

    def test_02_minus(self):
        self.arith_bash('1 - 2')
        self.arith_bash('-10 - -10')
        self.arith_bash('99999 - 1')
        self.arith_bash('10 - -20')
        self.arith_bash('1 - 0')

    def test_03_bang(self):
        self.arith_bash('!5')
        self.arith_bash('!(5 + 1)')
        self.arith_bash('!0')
        self.arith_bash('!(5 - 5)')

    def test_04_pow(self):
        self.arith_bash('5 ** 3')
        self.arith_bash('1 ** 0')
        self.arith_bash('0 ** 0')
        self.arith_bash('-4 ** 2')
        self.arith_bash('-5 ** 2')

    def test_05_mult(self):
        self.arith_bash('5 * 3')
        self.arith_bash('1 * 0')
        self.arith_bash('0 * 0')
        self.arith_bash('-4 * -2')
        self.arith_bash('5 * -2')

    def test_06_div(self):
        self.arith_bash('1000 / 5')
        self.arith_bash('5 / 3')
        self.arith_bash('-4 / -2')
        self.arith_bash('5 / -2')

    def test_07_bit_and(self):
        self.arith_bash('5 & 3')
        self.arith_bash('1 & 0')
        self.arith_bash('0 & 0')
        self.arith_bash('-4 & 2')
        self.arith_bash('-5 & 2')

    def test_08_bit_xor(self):
        self.arith_bash('5 ^ 3')
        self.arith_bash('1 ^ 0')
        self.arith_bash('0 ^ 0')
        self.arith_bash('-4 ^ 2')
        self.arith_bash('-5 ^ 2')

    def test_08_bit_or(self):
        self.arith_bash('5 | 3')
        self.arith_bash('1 | 0')
        self.arith_bash('0 | 0')
        self.arith_bash('-4 | 2')
        self.arith_bash('-5 | 2')

    def test_09_bool_and(self):
        self.arith_bash('5 && 3')
        self.arith_bash('1 && 0')
        self.arith_bash('0 && 0')
        self.arith_bash('-4 && 2')
        self.arith_bash('-5 && 2')
    
    def test_10_bool_or(self):
        self.arith_bash('5 || 3')
        self.arith_bash('1 || 0')
        self.arith_bash('0 || 0')
        self.arith_bash('-4 || 2')
        self.arith_bash('-5 || 2')

    def test_11_pars(self):
        self.arith_bash('3 * (5 || 3)')
        self.arith_bash('1*(4*3)')
        self.arith_bash('5+(3/7)')
        self.arith_bash('(12 ^56) ** (6 && 6)')
