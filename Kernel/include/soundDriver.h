#include <stdint.h>

int beepasm();
int unbeepasm();
void beep(uint64_t ticks,uint64_t frequency);
void activateBeep();
void deactivateBeep();
void set_frequency(int64_t frequency);

void set_frequencyASM(int64_t frenquency);
uint64_t init_sound();