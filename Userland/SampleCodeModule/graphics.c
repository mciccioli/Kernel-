
#include <callSyscall.h>
#include <graphics.h>




static uint64_t SCREEN_HEIGHT;
static uint64_t SCREEN_WIDTH;



const uint64_t getScreenWidth(){
	return callSyscall(WIDTH,(void*)0,(void*)0,(void*)0,(void*)0,(void*)0,(void*)0);
}
const uint64_t getScreenHeight(){
	return callSyscall(HEIGHT,(void*)0,(void*)0,(void*)0,(void*)0,(void*)0,(void*)0);
}

uint64_t drawRect(int64_t x,int64_t y,uint64_t width,uint64_t height,int64_t color){
	
	for(int i = x; i<  x + width;i++ ){
		for(int j = y; j < y + height; j++){
			if(drawPixel(i,j,color) == 0){
				return 0;
			}
		}
	}
	return 1;
}

uint64_t drawCircle(int64_t x,int64_t y,int64_t radius,int64_t color){

	for(int i = -radius ; i <= radius ; i++){
		for(int j = -radius ; j <= radius; j++){
			if(i*i + j*j <= radius*radius){
				if(drawPixel(x+i,y+j,color) == 0){
					return 0;
				}
			}
		}
	}
	return 1;

}

uint64_t clearScreen(){
	return callSyscall(CLEAR,(void*)0,(void*)0,(void*)0,(void*)0,(void*)0,(void*)0);
}

uint64_t drawPixel(int64_t x, int64_t y, int64_t color){
	return callSyscall(DRAW_PIXEL,(void*)x,(void*)y,(void*)color,(void*)0,(void*)0,(void*)0);
}

uint64_t drawText(char * s,int64_t x, int64_t y,uint64_t fontColor,uint64_t backgroundColor){
	while(*s){
		callSyscall(DRAW_CHAR,(void*)x,(void*)y,(void*)*s,(void*)fontColor,(void*)backgroundColor,(void*)0);
		x+= CHAR_WIDTH;
		s++;
	}
	return 1;
}

void init(){
 SCREEN_WIDTH = getScreenWidth();
 SCREEN_HEIGHT = getScreenHeight();
}
