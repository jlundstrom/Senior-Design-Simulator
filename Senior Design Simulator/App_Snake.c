#include "App_Basic.h"
#include "Draw.h"
#include "Input.h"
#include "Random.h"

#define DIRECTION_UP 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 4
#define DIRECTION_RIGHT 8
#define SEGMENT_ACTIVE 16

struct appData {	
	unsigned char headX;
	unsigned char headY;
	unsigned short headIdx;
	unsigned short length;
	char frame;
	unsigned char Direction;
	unsigned char pastKeys;
	Pixel p;
	Pixel Blank;
	unsigned char snake[WIDTH*HEIGHT];
} typedef appData;
appData* Data;

void App_Snake_Init(void);
void App_Snake_Deinit(void);

void Demo_Snake_Init(void) {
	App_Snake_Init();
}

void Demo_Snake_Tick(void) {
}

void Demo_Snake_Deinit(void) {
	App_Snake_Deinit();
}

void App_Snake_Init(void) {
	Data = &AppStorage;
	Data->headX = 0;
	Data->headY = 2;
	Data->headIdx = 0;
	Data->length = 1;
	Data->frame = 0;
	Data->p.R = 128;
	Data->p.G = 128;
	Data->p.B = 0;
	Data->Blank.R = 0;
	Data->Blank.G = 0;
	Data->Blank.B = 0;
	Data->snake[0] = DIRECTION_RIGHT | SEGMENT_ACTIVE;
}

void App_Snake_Remove_Tail() {
	unsigned char x, y;
	unsigned short idx, offset;
	x = Data->headX;
	y = Data->headY;
	offset = Data->headIdx;

	// Consider storing the tail end, and detecting what the next peice is by scanning the 4 neighbors.

	for (idx = 0; idx < Data->length; idx++) {
		if (offset - idx == 0 ) {
			offset += WIDTH * HEIGHT;
		}
		switch (Data->snake[offset - idx] & ~SEGMENT_ACTIVE)
		{
		case DIRECTION_UP:
			y++;
			break;
		case DIRECTION_DOWN:
			y--;
			break;
		case DIRECTION_LEFT:
			x++;
			break;
		case DIRECTION_RIGHT:
			x--;
			break;
		default:
			break;
		}
	}
	idx--;
	Data->snake[offset - idx] = 0;
	setPixel(x, y, Data->Blank);
}

void App_Snake_Tick(void) {
	unsigned char Input;
	if (Data->frame == 6) {
		Data->frame = 0;
		if (Data->Direction & SEGMENT_ACTIVE) {
			Data->Direction ^= SEGMENT_ACTIVE;
			Data->length++;
		}
		else {
			App_Snake_Remove_Tail();
		}
		Input = Input_Status & ~Data->pastKeys;
		Data->pastKeys = Input_Status & 0xFF;
		if (Input) {
			if (Input & UP_INPUT && Data->Direction != DIRECTION_DOWN) {
				Data->Direction = DIRECTION_UP;
			} else if (Input & DOWN_INPUT && Data->Direction != DIRECTION_UP) {
				Data->Direction = DIRECTION_DOWN;
			} else if (Input & LEFT_INPUT && Data->Direction != DIRECTION_RIGHT) {
				Data->Direction = LEFT_INPUT;
			} else if (Input & RIGHT_INPUT && Data->Direction != DIRECTION_LEFT) {
				Data->Direction = DIRECTION_RIGHT;
			}
			if (Input & A_INPUT) {
				Data->Direction |= SEGMENT_ACTIVE;
			}

			if (Data->headX < 0|| Data->headX > WIDTH) {
				Data->Direction |= SEGMENT_ACTIVE;
				return;
			}

			if (Data->headY < 0 || Data->headY > HEIGHT) {
				Data->Direction |= SEGMENT_ACTIVE;
				return;
			}
		}
		switch (Data->Direction & ~SEGMENT_ACTIVE)
		{
		case DIRECTION_UP:
			Data->headY--;
			break;
		case DIRECTION_DOWN:
			Data->headY++;
			break;
		case DIRECTION_LEFT:
			Data->headX--;
			break;
		case DIRECTION_RIGHT:
			Data->headX++;
			break;
		default:
			break;
		}
		setPixel(Data->headX, Data->headY, Data->p);
		Data->headIdx = (Data->headIdx + 1) % (WIDTH * HEIGHT);
		Data->snake[Data->headIdx] = Data->Direction & ~SEGMENT_ACTIVE;
	}
	Data->frame++;
}

void App_Snake_Deinit(void) {
	Data->headX = 0;
	Data->headY = 0;
	Data->frame = 0;
	Data->p.R = 128;
	Data->p.G = 128;
	Data->p.B = 0;
	Data->Blank.R = 0;
	Data->Blank.G = 0;
	Data->Blank.B = 0;

	Data = 0;
}

void App_Snake_New(App* app) {
	app->Demo_Init = &Demo_Snake_Init;
	app->Demo_Tick = &Demo_Snake_Tick;
	app->Demo_Deinit = &Demo_Snake_Deinit;
	app->App_Init = &App_Snake_Init;
	app->App_Tick = &App_Snake_Tick;
	app->App_Deinit = &App_Snake_Deinit;
}