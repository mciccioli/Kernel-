#ifndef SYS_CALLS_H
#define SYS_CALLS_H
#include <stdint.h>
uint64_t sys_write(uint64_t fd,const char* buffer,uint64_t count);
uint64_t sys_read(uint64_t fd,char * buffer,uint64_t count);

uint64_t sys_getHeight();
uint64_t sys_getWidth();
uint64_t sys_sleep(int ticks);
uint64_t sys_beep(uint64_t timer,int64_t frequency);
uint64_t sys_time();
uint64_t sys_seconds_elapsed();
uint64_t sys_drawPixel(int64_t x, int64_t y, uint64_t color);
uint64_t sys_clear();
uint64_t sys_drawChar(int64_t x, int64_t y, char character, uint64_t fontColor,uint64_t backgroundColor);

void _sti();


#endif