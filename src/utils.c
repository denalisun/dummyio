#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// This code will be very inefficient but it hopefully will workYaya
const char* int_to_roman(int num)
{
    const char* romanNumerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int romanValues[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

    char toReturn[20];
    if (num <= 0) return NULL;
    for (int i = 0; i < 13; i++)
    {
        if (num >= romanValues[i])
        {
            strcat(toReturn, romanNumerals[i]);
        }
    }
    strcat(toReturn, "\0");

    char* ptr = malloc(strlen(toReturn)+1);
    strcpy(ptr, toReturn);
    return ptr;
}
