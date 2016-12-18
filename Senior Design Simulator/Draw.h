#pragma once

#ifdef DEBUG
#define WIDTH 32
#define HEIGHT 16
#else
#define WIDTH 32
#define HEIGHT 16
#endif // DEBUG

struct pixel {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} typedef Pixel;

Pixel Pixels[WIDTH * HEIGHT];
Pixel getPixel(int x, int y);
void setPixel(int x, int y, Pixel pixel);
void drawRect(int x, int y, int w, int h, Pixel pixel);