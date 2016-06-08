import unittest
from cffi import FFI
from test_functions import *


class TestHashtable(unittest.TestCase):
    def __init__(self, arg):
        unittest.TestCase.__init__(self, arg)
        self.ffi = FFI()
        self.lib = self.ffi.dlopen("../build/libmy42sh.so")
        source = get_source_all_files("../src/includes")
        self.ffi.cdef(source)
        self.fev_fct = self.ffi.NULL

    def test_01_hashtable_invalid_init(self):
        chashtable = self.lib.ht_init(0, self.fev_fct)
        self.assertEqual(self.ffi.NULL, chashtable)

    def test_02_hashtable_valid_init(self):
        chashtable = self.lib.ht_init(100, self.fev_fct)
        self.assertIsNotNone(chashtable)
        self.assertEqual(0, self.lib.ht_size(chashtable))

        self.lib.ht_destroy(chashtable)

    def test_03_hashtable_add_element_simple(self):
        chashtable = self.lib.ht_init(100, self.fev_fct)

        self.assertEqual(0, self.lib.ht_size(chashtable))
        self.lib.ht_insert(chashtable, b'test', b'thomasdom')
        self.assertEqual(1, self.lib.ht_size(chashtable))

        self.lib.ht_destroy(chashtable)

    def test_04_hashtable_get_element_simple(self):
        chashtable = self.lib.ht_init(100, self.fev_fct)

        self.lib.ht_insert(chashtable, b'test', b'passed')
        self.lib.ht_insert(chashtable, b'kapten', b'thomasdom')
        self.lib.ht_insert(chashtable, b'abcd', b'efghij')
        self.lib.ht_insert(chashtable, b'azerty', b'uiop')

        celement = self.lib.ht_get(chashtable, b'kapten')

        self.assertEqual(b'kapten', self.ffi.string(celement.key))
        self.assertEqual(b'thomasdom', self.ffi.string(
            self.ffi.cast("char *", celement.value)))

        celement = self.lib.ht_get(chashtable, b'azerty')

        self.assertEqual(b'azerty', self.ffi.string(celement.key))
        self.assertEqual(b'uiop', self.ffi.string(
            self.ffi.cast("char *", celement.value)))

        self.lib.ht_destroy(chashtable)

    def test_05_hashtable_replace_element_simple(self):
        chashtable = self.lib.ht_init(100, self.fev_fct)

        self.lib.ht_insert(chashtable, b'kapten', b'mrpandat')
        self.assertEqual(1, self.lib.ht_size(chashtable))

        celement = self.lib.ht_get(chashtable, b'kapten')

        self.assertEqual(b'kapten', self.ffi.string(celement.key))
        self.assertEqual(b'mrpandat', self.ffi.string(
            self.ffi.cast("char *", celement.value)))

        self.lib.ht_insert(chashtable, b'kapten', b'thomasdom')
        self.assertEqual(1, self.lib.ht_size(chashtable))

        celement = self.lib.ht_get(chashtable, b'kapten')

        self.assertEqual(b'kapten', self.ffi.string(celement.key))
        self.assertEqual(b'thomasdom', self.ffi.string(
            self.ffi.cast("char *", celement.value)))

        self.lib.ht_destroy(chashtable)

    def test_06_hashtable_remove_element_simple(self):
        chashtable = self.lib.ht_init(100, self.fev_fct)

        self.lib.ht_insert(chashtable, b'test', b'passed')
        self.lib.ht_insert(chashtable, b'kapten', b'thomasdom')
        self.lib.ht_insert(chashtable, b'abcd', b'efghij')
        self.lib.ht_insert(chashtable, b'azerty', b'uiop')

        self.assertEqual(4, self.lib.ht_size(chashtable))

        celement = self.lib.ht_get(chashtable, b'kapten')

        self.assertEqual(b'kapten', self.ffi.string(celement.key))
        self.assertEqual(b'thomasdom', self.ffi.string(
            self.ffi.cast("char *", celement.value)))

        self.lib.ht_remove(chashtable, b'kapten')

        self.assertEqual(3, self.lib.ht_size(chashtable))

        celement = self.lib.ht_get(chashtable, b'kapten')

        self.assertEqual(self.ffi.NULL, celement)

        self.lib.ht_destroy(chashtable)

    def test_07_hashtable_get_all_elements_simple(self):
        # TODO: Implement hashtable_get_all_elements_simple test
        pass

    def test_08_hashtable_remove_all_elements_simple(self):
        chashtable = self.lib.ht_init(100, self.fev_fct)

        self.lib.ht_insert(chashtable, b'test', b'passed')
        self.lib.ht_insert(chashtable, b'kapten', b'thomasdom')
        self.lib.ht_insert(chashtable, b'abcd', b'efghij')
        self.lib.ht_insert(chashtable, b'azerty', b'uiop')

        self.assertEqual(4, self.lib.ht_size(chashtable))

        self.lib.ht_remove_all(chashtable)

        self.assertEqual(0, self.lib.ht_size(chashtable))

        celement = self.lib.ht_get(chashtable, b'kapten')

        self.assertEqual(self.ffi.NULL, celement)

        self.lib.ht_destroy(chashtable)
