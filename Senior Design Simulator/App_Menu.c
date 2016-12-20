#include "App_Menu.h"
#include "Input.h"
#include "Draw.h"

int idx;
int frame;
int x, y;
unsigned char pastKeys;

void App_Menu_Init(void) {	
	clearDisplay();
	idx = 0;
	frame = 0;
	apps[idx].Demo_Init();
	setPixel(0, idx, PIXEL_GREEN);
}

void App_Menu_Tick(void) {
	unsigned char Input;
	if (frame == 4) {
		Input = Input_Status & ~pastKeys;
		pastKeys = Input_Status;
		frame = 0;
		if (Input) {
			if (Input_Status & UP_INPUT) {
				setPixel(0, idx, PIXEL_BLACK);
				apps[idx].Demo_Deinit();
				idx--;
			}
			if (Input_Status & DOWN_INPUT) {
				setPixel(0, idx, PIXEL_BLACK);
				apps[idx].Demo_Deinit();
				idx++;
			}
			if (idx < 0) {
				idx = 0;
			}
			if (idx >= APP_COUNT) {
				idx = APP_COUNT-1;
			}
			if (Input_Status &(UP_INPUT | DOWN_INPUT)) {
				drawRect(2, 0, WIDTH, HEIGHT, PIXEL_BLACK);
				apps[idx].Demo_Init();
				setPixel(0, idx, PIXEL_GREEN);
			}
			if (Input_Status & A_INPUT) {
				apps[idx].Demo_Deinit();
				currentApp = &apps[idx];
				clearDisplay();
				currentApp->App_Init();
				idx = -1;
			}
		}
	}
	if (idx != -1) {
		apps[idx].Demo_Tick();
		frame++;
	}
}

void App_Menu_Deinit(void) {

}

void App_Menu_New(App* app) {
	app->Demo_Init = 0;
	app->Demo_Tick = 0;
	app->Demo_Deinit = 0;
	app->App_Init = &App_Menu_Init;
	app->App_Tick = &App_Menu_Tick;
	app->App_Deinit = &App_Menu_Deinit;
}

void App_Menu_Poll() {
	if (Input_Status & START_INPUT) {
		if (currentApp != &homeApp) {
			currentApp->App_Deinit();
			currentApp = &homeApp;
			currentApp->App_Init();
		}
	}
}