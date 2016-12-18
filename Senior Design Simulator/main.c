#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Display.h"
#include "Draw.h"

int getch_noblock() {
	if (_kbhit())
		return _getch();
	else
		return -1;
}

int main() {
	Pixel p = { 128,128,0 };
	Pixel Blank = { 0,0,0 };
	int x = 2, y = 0, chr;
	Display_init();

	setPixel(x, y, p);
	while (1) {
		chr = getch_noblock();
		if (chr > 0) {
			setPixel(x, y, Blank);
			if (chr == 'w') {
				y--;
			}else if (chr == 's') {
				y++;
			}else if (chr == 'a') {
				x--;
			}
			else if (chr == 'd') {
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
	}

	Draw();
	return 0;
}