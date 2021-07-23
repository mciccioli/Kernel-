#include <stdint.h>
#include <syscalls.h>


#define WIDTH 1
#define HEIGHT 2
#define READ 3
#define WRITE 4
#define SPEAKER 5 
#define SLEEP 6
#define TIME 7
#define CLEAR 8
#define SECONDS_ELAPSED 9
#define DRAW_PIXEL 10
#define DRAW_CHAR 11
#define ERROR -1


typedef uint64_t(*SystemCall)();

static SystemCall syscall_array[] = {0,(SystemCall)sys_getWidth,(SystemCall)sys_getHeight,(SystemCall)sys_read,(SystemCall)sys_write,(SystemCall) sys_beep,(SystemCall)sys_sleep,(SystemCall) sys_time,(SystemCall) sys_clear,(SystemCall) sys_seconds_elapsed, (SystemCall) sys_drawPixel,(SystemCall)sys_drawChar};

uint64_t syscallDispatcher(uint64_t id, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6){
   return syscall_array[id](param1,param2,param3,param4,param5,param6);
}




