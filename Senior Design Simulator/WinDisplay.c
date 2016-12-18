#include "Display.h"
#include "Draw.h"
#include <windows.h>

#define	BLUE 0x10
#define	GREEN 0x20
#define	RED 0x40
#define	LIGHTBLUE 0x90
#define	LIGHTGREEN 0xA0
#define	LIGHTRED 0xB0
HANDLE Handle;

void Display_init() {
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleOutputCP(65001);
}

void Draw(void) {
	int x, y;
	COORD t;
	unsigned char color;
	DWORD size = 2;
	DWORD  ret;
	Pixel pixel;


	for (x = 0; x < 32; x++) {
		for (y = 0; y < 16; y++) {
			color = 0;
			t.X = x;
			t.Y = y;

			pixel = getPixel(x, y);

			if (pixel.R > 128) {
				color |= RED;
			}
			else if (pixel.R > 0) {
				color |= LIGHTRED;
			}
			if (pixel.G > 128) {
				color |= GREEN;
			}
			else if (pixel.G > 0) {
				color |= LIGHTGREEN;
			}
			if (pixel.B > 128) {
				color |= BLUE;
			}
			else if (pixel.B > 0) {
				color |= LIGHTBLUE;
			}

			FillConsoleOutputCharacter(Handle, (TCHAR) '█', size, t, &ret);
			FillConsoleOutputAttribute(Handle, color, size, t, &ret);
		}
	}
}