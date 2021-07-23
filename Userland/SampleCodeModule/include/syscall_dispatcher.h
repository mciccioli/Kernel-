
#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <stdint.h>
#include <callSyscall.h>


#define WIDTH 1
#define HEIGHT 2
#define READ 3
#define WRITE 4
#define SPEAKER 5 
#define DRAW_RECT 6
#define SLEEP 7
#define DRAW_CIRCLE 8
#define TIME 9
#define CLEAR 10
#define SECONDS_ELAPSED 11
#define ERROR -1

void sys_write(char * string, int size);
char sys_read(char * string, int size);
void sys_beep(void);
void sys_new_line(void);
