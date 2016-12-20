#include "App_Basic.h"
#include "Draw.h"
#include "Input.h"
#include "Random.h"

#define DIRECTION 0xF
#define DIRECTION_UP 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 4
#define DIRECTION_RIGHT 8
#define SEGMENT_ACTIVE 16
#define GAME_OVER 32

struct appData {	
	unsigned char headX;
	unsigned char headY;
	unsigned char foodX;
	unsigned char foodY;
	unsigned short headIdx;
	unsigned short length;
	char frame;
	unsigned char Direction;
	unsigned char pastKeys;
	unsigned char snake[WIDTH*HEIGHT];
} typedef appData;
appData* Data;

void App_Snake_Init(void);
void App_Snake_Deinit(void);
void App_Snake_Place_Food(void);

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
	Data->headX = getRandom() % WIDTH;
	Data->headY = getRandom() % HEIGHT;
	Data->headIdx = 0;
	Data->length = 1;
	Data->frame = 0;

	Data->snake[0] = DIRECTION_RIGHT | SEGMENT_ACTIVE;
	App_Snake_Place_Food();
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
	setPixel(x, y, PIXEL_BLACK);
}

void App_Snake_Place_Food() {
	Pixel tmp;
	while(1) {
		Data->foodX = getRandom() % WIDTH;
		Data->foodY = getRandom() % HEIGHT;
		tmp = getPixel(Data->foodX, Data->foodY);
		if (tmp.R == tmp.G == tmp.B == 0) {
			break;
		}
	}
	setPixel(Data->foodX, Data->foodY, PIXEL_GREEN);
}

void App_Snake_Game_Over_Tick(){
	if (Data->frame % 4 == 3) {
		setPixel(getRandom() % WIDTH, getRandom() % HEIGHT, PIXEL_RED);
		if (Input_Status & ~Data->pastKeys) {
			clearDisplay();
			App_Snake_Deinit();
			App_Snake_Init();
		}
		Data->pastKeys = Input_Status & 0xFF;
	}
}

void App_Snake_Tick(void) {
	unsigned char Input;
	Pixel tmp;
	if (Data->Direction & GAME_OVER) {
		App_Snake_Game_Over_Tick();
	}
	else if (Data->frame == 6) {
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
			if (!Data->Direction) {
				return;
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
		tmp = getPixel(Data->headX, Data->headY);
		if (Data->foodX == Data->headX && Data->foodY == Data->headY) {
			Data->Direction |= SEGMENT_ACTIVE;
			App_Snake_Place_Food();
		} else if (tmp.R || tmp.G || tmp.B || Data->headX < 0 || 
			Data->headX >= WIDTH || Data->headY < 0 || Data->headY >= HEIGHT) {
			Data->Direction = GAME_OVER;
		}
		setPixel(Data->headX, Data->headY, PIXEL_CYAN);
		Data->headIdx = (Data->headIdx + 1) % (WIDTH * HEIGHT);
		Data->snake[Data->headIdx] = Data->Direction & DIRECTION;		
	}
	Data->frame++;
}

void App_Snake_Deinit(void) {
	int i;
	for (i = 0; i < sizeof(appData); i++) {
		AppStorage[i] = 0;
	}

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