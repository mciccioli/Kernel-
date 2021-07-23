#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>
void ncPrint(const char * string);
void ncPrintChar(char character);
void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncPrintWithColor(const char * string,uint64_t color);
void ncPrintCharWithColor(char character,uint64_t color);
void ncPrintInPos(const char * string, uint8_t * wantedVideo);

#endif