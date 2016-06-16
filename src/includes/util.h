/**
 ** @file util.h
 ** @brief General functions which are used in all kind of scenarios
 ** in the project
 ** @author Moisan L, Lees M
 */

#ifndef INC_42SH_UTIL_H
#define INC_42SH_UTIL_H

#include "../includes/global.h"

/**
 ** @fn str_append(char *str_one, char *str_two)
 ** @brief appends two strings togethen, struct list *lst)r
 ** @param string 1
 ** @param string 2
 ** @return the resulting string
 */
char *str_append(char *str_one, char *str_two);

char *str_append_free(char *str_one, char *str_two);

/**
 ** @fn char *args_from_str(char *str, char ***arguments)
 ** @brief extracts words from a string
 ** @param string to extract the words from
 ** @param array of string containing the words
 ** @return the first word
 */
char *args_from_str(char *str, char ***arguments);

/**
 ** @fn char *file_to_str(FILE *file)
 ** @brief reads a whole file in an str
 ** @param File to read from
 ** @return the red string
 */
char *file_to_str(FILE *file);
/**
 ** @fn char *path_to_str(char *file)
 ** @brief reads a whole file in an str
 ** @param path of the files to read from
 ** @return the red string
 */
char *path_to_str(char *file);

bool pattern_matching(char *str1, char *str2);

/**
 ** @fn test()
 ** @brief Used to debug some functions and the testsuite
 ** @return always 1
 */

int test();

char *my_itoa(int i);
int my_pow(int a, int b);


/**
 ** @fn int file_test(char *name);
 ** @brief tests if a file exists and if it's executable
 ** @param path to the file
 ** @return 0 if it's ok, 127 if it does not exists, 126 if it's not executable
 */
int file_test(char *name);

char *my_strcat(char *dest, char *src);

#endif
