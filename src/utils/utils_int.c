#include "../includes/global.h"

static unsigned int_width(int i)
{
    unsigned n = 0;
    if (i == 0)
        return 1;
    if (i < 0)
    {
        i = -i;
        n++;
    }
    while (i > 0)
    {
        i = (i - (i % 10)) / 10;
        n++;
    }
    return n;
}

char *my_itoa(int i)
{
    int size = int_width(i) + 1;
    char *str = malloc(size * sizeof (char));
    str[--size] = '\0';
    if (i == 0)
        str[--size] = '0';
    else if (i < 0)
    {
        str[0] = '-';
        i = -i;
    }
    while (i > 0)
    {
        str[--size] = '0' + i % 10;
        i = (i - (i % 10)) / 10;
    }
    return str;
}



