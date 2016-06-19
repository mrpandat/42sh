import unittest

from cffi import FFI

from .utils import *


class TextArlexOperatorsEasy(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)

        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)

        self.carlex = self.ffi.NULL

    def test_01_arlex_add_easy(self):
        init_and_process_arlex(self, b'2 + 3')

        self.assertTrue(
            arlex_list_equals(self, False,
                              (self.lib.AL_NUMBER, b'2'),
                              (self.lib.AL_PLUS, b'+'),
                              (self.lib.AL_NUMBER, b'3'),
                              (self.lib.AL_EOF, b'EOF'))
        )

        destroy_arlex(self)

    def test_02_arlex_minus_easy(self):
        init_and_process_arlex(self, b'4 - 0')

        self.assertTrue(
            arlex_list_equals(self, False,
                              (self.lib.AL_NUMBER, b'4'),
                              (self.lib.AL_MINUS, b'-'),
                              (self.lib.AL_NUMBER, b'0'),
                              (self.lib.AL_EOF, b'EOF'))
        )

        destroy_arlex(self)

    def test_03_arlex_multiply_easy(self):
        init_and_process_arlex(self, b'189 * 123')

        self.assertTrue(
            arlex_list_equals(self, False,
                              (self.lib.AL_NUMBER, b'189'),
                              (self.lib.AL_MULT, b'*'),
                              (self.lib.AL_NUMBER, b'123'),
                              (self.lib.AL_EOF, b'EOF'))
        )

        destroy_arlex(self)

    def test_04_arlex_divide_easy(self):
        init_and_process_arlex(self, b'234 / 456')

        self.assertTrue(
            arlex_list_equals(self, False,
                              (self.lib.AL_NUMBER, b'234'),
                              (self.lib.AL_DIV, b'/'),
                              (self.lib.AL_NUMBER, b'456'),
                              (self.lib.AL_EOF, b'EOF'))
        )

        destroy_arlex(self)

    def test_05_arlex_exponentiation_easy(self):
        init_and_process_arlex(self, b'10 ** 2')

        self.assertTrue(
            arlex_list_equals(self, False,
                              (self.lib.AL_NUMBER, b'10'),
                              (self.lib.AL_POW, b'**'),
                              (self.lib.AL_NUMBER, b'2'),
                              (self.lib.AL_EOF, b'EOF'))
        )

        destroy_arlex(self)
