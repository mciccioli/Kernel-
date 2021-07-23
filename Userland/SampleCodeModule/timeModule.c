#include <timeModule.h>
#include <stdint.h>
#include <callSyscall.h>

uint64_t getSeconds(){
	return callSyscall(SECONDS_ELAPSED,(void*)0,(void*)0,(void*)0,(void*)0,(void*)0,(void*)0);
}

uint64_t sleep(uint64_t ticks){
	return callSyscall(SLEEP,(void*)ticks,(void*)0,(void*)0,(void*)0,(void*)0,(void*)0);
}
