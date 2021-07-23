#include <soundDriver.h>
#include <time.h>
void beep(uint64_t ticks,uint64_t frequency){
set_frequency(frequency);
  activateBeep();
  	_sti();
  int end = ticks_elapsed() + ticks;
  while(ticks_elapsed() < end);
  deactivateBeep();

}

void activateBeep(){
  beepasm();
}

void deactivateBeep(){
  unbeepasm();
}

void set_frequency(int64_t frequency){
  //set_frequencyASM(1193180 / frequency);
  set_frequencyASM(frequency);
}