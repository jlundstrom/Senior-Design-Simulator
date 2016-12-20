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

static Pixel PIXEL_BLACK = { 0, 0, 0 };
static Pixel PIXEL_CYAN = { 0, 128, 128 };
static Pixel PIXEL_RED = { 128, 0, 0 };
static Pixel PIXEL_GREEN = { 0, 128, 0 };
static Pixel PIXEL_WHITE = { 255, 255, 255 };


Pixel Pixels[WIDTH * HEIGHT];
Pixel getPixel(int x, int y);
void setPixel(int x, int y, Pixel pixel);
void drawRect(int x, int y, int w, int h, Pixel pixel);
void clearDisplay(void);