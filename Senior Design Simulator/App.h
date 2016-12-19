#pragma once
#define APP_COUNT 1
typedef void voidFunc(void);

struct App {
	voidFunc* Demo_Init;
	voidFunc* Demo_Tick;
	voidFunc* Demo_Deinit;
	voidFunc* App_Init;
	voidFunc* App_Tick;
	voidFunc* App_Deinit;
}typedef App;

char AppStorage[256];

App apps[APP_COUNT];
App* currentApp;
App homeApp;