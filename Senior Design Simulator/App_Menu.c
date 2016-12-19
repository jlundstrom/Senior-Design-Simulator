#include "App_Menu.h"
#include "Input.h"
#include "Draw.h"

int idx;
int frame;
Pixel p = {0, 128, 128};
Pixel Blank = { 0, 0, 0 };
int x, y;
unsigned char pastKeys;

void App_Menu_Init(void) {	
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			setPixel(x, y, Blank);
		}
	}
	idx = 0;
	frame = 0;
	apps[idx].Demo_Init();
	setPixel(0, idx, p);
}

void App_Menu_Tick(void) {
	unsigned char Input;
	if (frame == 4) {
		Input = Input_Status & ~pastKeys;
		pastKeys = Input_Status;
		frame = 0;
		if (Input) {
			if (Input_Status & UP_INPUT) {
				apps[idx].Demo_Deinit();
				idx--;
			}
			if (Input_Status & DOWN_INPUT) {
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
				for (x = 2; x < WIDTH; x++) {
					for (y = 0; y < HEIGHT; y++) {
						setPixel(x, y, Blank);
					}
				}
				apps[idx].Demo_Init();
				setPixel(0, idx, p);
			}
			if (Input_Status & A_INPUT) {
				apps[idx].Demo_Deinit();
				currentApp = &apps[idx];
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