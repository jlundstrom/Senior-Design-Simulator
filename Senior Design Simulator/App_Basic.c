#include "App_Basic.h"
#include "Draw.h"
#include "Input.h"

struct appData {
	int x;
	int y;
	int frame;
	Pixel p;
	Pixel Blank;
	unsigned char pastKeys;
} typedef appData;
appData* Data;

void Demo_Init(void) {
	Data = &AppStorage;
	Data->x = 2;
	Data->y = 0;
	Data->frame = 0;
	Data->p.R = 128;
	Data->p.G = 128;
	Data->p.B = 0;
	Data->Blank.R = 0;
	Data->Blank.G = 0;
	Data->Blank.B = 0;
}

void Demo_Tick(void) {
	if (Data->frame == 4) {
		Data->frame = 0;
		setPixel(Data->x, Data->y, Data->Blank);
		Data->x++;
		if (Data->x == WIDTH) {
			Data->y++;
			Data->x = 2;
		}
		if (Data->y == HEIGHT) {
			Data->y = 0;
		}
		setPixel(Data->x, Data->y, Data->p);
	}
	Data->frame++;
}

void Demo_Deinit(void) {
	Data->x = 0;
	Data->y = 0;
	Data->frame = 0;
	Data->p.R = 0;
	Data->p.G = 0;
	Data->p.B = 0;
	Data->Blank.R = 0;
	Data->Blank.G = 0;
	Data->Blank.B = 0;

	Data = 0;
}

void App_Init(void) {
	Data = &AppStorage;
	Data->x = 2;
	Data->y = 0;
	Data->frame = 0;
	Data->p.R = 128;
	Data->p.G = 128;
	Data->p.B = 0;
	Data->Blank.R = 0;
	Data->Blank.G = 0;
	Data->Blank.B = 0;
}

void App_Tick(void) {
	unsigned char Input;
	if (Data->frame == 4) {
		Data->frame = 0;
		Input = Input_Status & ~Data->pastKeys;
		Data->pastKeys = Input_Status & 0xF0;
		if (Input) {
			setPixel(Data->x, Data->y, Data->Blank);
			if (Input & UP_INPUT) {
				Data->y--;
			}
			if (Input & DOWN_INPUT) {
				Data->y++;
			}
			if (Input & LEFT_INPUT) {
				Data->x--;
			}
			if (Input & RIGHT_INPUT) {
				Data->x++;
			}
			if (Input & A_INPUT) {
				if (Data->p.R == 0) {
					Data->p.R = 128;
				}else if (Data->p.R == 128) {
					Data->p.R = 255;
				} else {
					Data->p.R = 0;
				}
			}
			if (Input & B_INPUT) {
				if (Data->p.G == 0) {
					Data->p.G = 128;
				}
				else if (Data->p.G == 128) {
					Data->p.G = 255;
				}
				else {
					Data->p.G = 0;
				}
			}

			if (Data->x < 0) {
				Data->x = WIDTH - 1;
			}

			if (Data->y < 0) {
				Data->y = HEIGHT - 1;
			}
			Data->x = Data->x % WIDTH;
			Data->y = Data->y % HEIGHT;
			setPixel(Data->x, Data->y, Data->p);
		}		
	}
	Data->frame++;
}

void App_Deinit(void) {
	Data->x = 0;
	Data->y = 0;
	Data->frame = 0;
	Data->p.R = 0;
	Data->p.G = 0;
	Data->p.B = 0;
	Data->Blank.R = 0;
	Data->Blank.G = 0;
	Data->Blank.B = 0;

	Data = 0;
}

void App_Basic_New(App* app) {
	app->Demo_Init = &Demo_Init;
	app->Demo_Tick = &Demo_Tick;
	app->Demo_Deinit = &Demo_Deinit;
	app->App_Init = &App_Init;
	app->App_Tick = &App_Tick;
	app->App_Deinit = &App_Deinit;
}