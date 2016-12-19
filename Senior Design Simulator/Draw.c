#include "Draw.h"

Pixel getPixel(int x, int y) {
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0) {
		return Pixels[0];
	}
	return Pixels[y * WIDTH + x];
}

void setPixel(int x, int y, Pixel pixel) {
	Pixels[y * WIDTH + x] = pixel;
}

void drawRect(int x, int y, int x2, int y2, Pixel pixel) {
	if (x2 > WIDTH) {
		x2 = WIDTH;
	}
	if (y2 > HEIGHT) {
		y2 = HEIGHT;
	}
	for (x = 0; x < x2; x++) {
		for (y = 0; y < y2; y++) {
			setPixel(x, y, pixel);
		}
	}
}

void clearDisplay(void) {
	Pixel blank = { 0,0,0 };
	drawRect(0, 0, WIDTH, HEIGHT, blank);
}