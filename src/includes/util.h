#ifndef INC_42SH_UTIL_H
#define INC_42SH_UTIL_H

char *str_append(char *str_one, char *str_two);
int test();
char *args_from_str(char *str, char ***arguments);
char *file_to_str(FILE *file);
char *path_to_str(char *file);
#endif
