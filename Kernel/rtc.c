#include <stdint.h>
#include <rtc.h>
#include <stdout.h>
#include <lib.h>

void displayDateTime(){
	getCurrDate();
	drawString(" - ");
	getCurrTime();
}

void getCurrTime(){
	char hs[3];
	intToBase(getCurrHs(),hs,10);
	char mins[3];
	intToBase(getCurrMins(),mins,10);
	char secs[3];
	intToBase(getCurrSecs(),secs,10);
	drawString(hs);
	drawChar(':',0xFFFFFF,0x000000);	
	drawString(mins);
	drawChar(':',0xFFFFFF,0x000000);	
	drawString(secs);
}

void getCurrDate(){
	char day[3];
	intToBase(getCurrDay(),day,10);
	char month[3];
	intToBase(getCurrMonth(),month,10);
	char year[3];
	intToBase(getCurrYear(),year,10);
	drawString(day);
	drawChar('/',0xFFFFFF,0x000000);	
	drawString(month);
	drawChar('/',0xFFFFFF,0x000000);	
	drawString(year);
}