#ifndef STDOUT_H
#define STDOUT_H

#include <stdint.h>
void drawChar(char character,int fontColor, int backgroundColor);
void newline();
void deleteChar();
void drawString(const char *string);
void drawStringWithColor(const char *string, int fontColor, int backgroundColor);
unsigned int getScreenWidth();
unsigned int getScreenHeight();
void clear();
#endif