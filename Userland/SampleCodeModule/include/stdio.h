#ifndef STDIO_H
#define STDIO_H
#include <stdarg.h>
#include <stdint.h>


#define MAX_LENGHT 500
void printf(const char* format, ...);
void putchar(char letter);
char getchar();
int scanf(char* format, ...);
void perror(const char* buffer);
void printBin(uint64_t value);
void printDec(uint64_t value);
void printHexa(uint64_t value);
void printBase(uint64_t value, uint64_t base);
#endif