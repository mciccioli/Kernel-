#ifndef LIB_H
#define LIB_H
#include <stdint.h>

char* intToBase(int num, char* str, int base);
void reverse(char str[], int length);
void swap ( char *str1, char *str2 );
uint64_t atoi(char* s);
#endif