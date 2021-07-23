#include <stdint.h>
#include <video_vm.h>
#include <font.h>

static unsigned int SCREEN_WIDTH = 1024;
static unsigned int SCREEN_HEIGHT = 768;
static unsigned int SCREEN_bPP = 3;

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

struct vbe_mode_info_structure * screenData = (void*)0x5C00;

void init_VM_Driver() {
	SCREEN_bPP = screenData->bpp / 8;
	SCREEN_HEIGHT = screenData->height;
	SCREEN_WIDTH = screenData->width;
}

void drawPixel(unsigned int x, unsigned int y,unsigned int color)
{
    char* screen = screenData->framebuffer; 
    unsigned where = (x + y*SCREEN_WIDTH) * SCREEN_bPP;
    screen[where] = color & 255;              // BLUE
    screen[where + 1] = (color >> 8) & 255;   // GREEN
    screen[where + 2] = (color >> 16) & 255;  // RED
}

uint32_t getFrameBuffer(){
	return screenData->framebuffer;
}

unsigned int getScreenHeight(){
	return screenData->height;
}

unsigned int getScreenWidth(){
	return screenData->width;
}

unsigned int getScreenBPP(){
	return screenData->bpp / 8;
}
void drawCharAt(int x, int y, char character, unsigned int fontColor,unsigned int backgroundColor){
	int aux_x = x;
	int aux_y = y;
	char bitIsPresent;
	unsigned char* toDraw = charBitmap(character);

	for(int i = 0 ; i < CHAR_HEIGHT ; i++){
		for(int j = 0; j < CHAR_WIDTH; j++){
			bitIsPresent = (1 << (CHAR_WIDTH - j)) & toDraw[i];
			if(bitIsPresent){
				drawPixel(aux_x,aux_y,fontColor);
			}
			else{
				drawPixel(aux_x,aux_y,backgroundColor);
			}
			aux_x++;
		}
		aux_x = x;
		aux_y += 1;
	}
}