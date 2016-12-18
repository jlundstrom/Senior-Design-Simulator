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

void drawRect(int x, int y, int w, int h, Pixel pixel) {
	Pixels[y * WIDTH + x] = pixel;
}