#include <stdio.h>
//#include <windows.h>
#include <conio.h>
#include "Display.h"
#include "Draw.h"
#include "Input.h"

int main() {
	Pixel p = { 128,128,0 };
	Pixel Blank = { 0,0,0 };
	int x = 2, y = 0;
	Display_init();
	Input_init();

	while (1) {
		if (Input_Status) {
			setPixel(x, y, Blank);
			if (Input_Status & UP_INPUT) {
				y--;
			}
			if (Input_Status & DOWN_INPUT) {
				y++;
			}
			if (Input_Status & LEFT_INPUT) {
				x--;
			}
			if (Input_Status & RIGHT_INPUT) {
				x++;
			}

			if (x < 0) {
				x = WIDTH - 1;
			}

			if (y < 0) {
				y = HEIGHT - 1;
			}
			x = x % WIDTH;
			y = y % HEIGHT;
			setPixel(x, y, p);
		}
		Draw();
		Input_Poll();
		printf("Input: %02X\n", Input_Status);
		printf("FPS: %02d\n", FPS);
	}

	Draw();
	return 0;
}