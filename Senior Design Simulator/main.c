#include <stdio.h>
//#include <windows.h>
//#include <conio.h>
#include "Display.h"
#include "Draw.h"
#include "Input.h"
#include "App.h"
#include "App_Basic.h"
#include "App_Menu.h"

int main() {
	App_Menu_New(&homeApp);
	App_Basic_New(&apps[0]);
	App_Snake_New(&apps[1]);

	Display_init();
	Input_init();
	currentApp = &homeApp;
	currentApp->App_Init();

	while (!(Input_Status & SELECT_INPUT)) {
		App_Menu_Poll();
		currentApp->App_Tick();
		Draw();
		Input_Poll();
		printf("Input: %02X\n", Input_Status);
		printf("FPS: %02d\n", FPS);
	}
	
	return 0;
}