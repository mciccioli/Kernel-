#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
uint64_t drawRect(int64_t x,int64_t y,uint64_t width,uint64_t height,int64_t color);
const uint64_t getScreenHeight();
const uint64_t getScreenWidth();
void init();

uint64_t clearScreen();
uint64_t drawCircle(int64_t x,int64_t y,int64_t radius,int64_t color);

uint64_t drawPixel(int64_t x, int64_t y, int64_t color);
uint64_t drawText(char * s,int64_t x, int64_t y,uint64_t fontColor,uint64_t backgroundColor);
typedef struct rectangleStruct{
	int x,y,height,width,color;

}Rectangle;

typedef struct circleStruct{
	int x,y,color;
	int radius;

}Circle;


#endif