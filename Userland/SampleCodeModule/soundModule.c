#include <soundModule.h>
#include <callSyscall.h>
void beep(uint64_t time,int64_t frequency){
	callSyscall(SPEAKER,(void*)time,(void*)frequency,(void*)0,(void*)0,(void*)0,(void*)0);
}