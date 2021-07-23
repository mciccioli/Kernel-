#include <time.h>
#include <stdint.h>
#include <kbDriver.h>

static void int_20();
static void int_21();

void irqDispatcher(uint64_t irq) {
	void (*functions[])() = {int_20,int_21};
	(*functions[irq])();
	return;
}

void int_21(){
	keyboardHandler();
}

void int_20() {
	timer_handler();
}
