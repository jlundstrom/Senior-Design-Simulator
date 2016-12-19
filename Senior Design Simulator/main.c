#include <stdio.h>
//#include <windows.h>
//#include <conio.h>
#include "Display.h"
#include "Draw.h"
#include "Input.h"
#include "App.h"
#include "App_Basic.h"

int main() {
	Pixel p = { 128,128,0 };
	Pixel Blank = { 0,0,0 };
	App apps[1];
	App* currentApp;
	int x = 2, y = 0;
	Display_init();
	Input_init();

	App_Basic_New(&apps[0]);
	currentApp = &apps[0];
	currentApp->App_Init();
	while (1) {
		currentApp->App_Tick();
		Draw();
		Input_Poll();
		printf("Input: %02X\n", Input_Status);
		printf("FPS: %02d\n", FPS);
	}
	
	return 0;
}