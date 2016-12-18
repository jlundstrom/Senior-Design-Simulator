#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Display.h"

int getch_noblock() {
	if (_kbhit())
		return _getch();
	else
		return -1;
}

int main() {
	Display_init();
	
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO ScreenInfo = calloc(sizeof(PCONSOLE_SCREEN_BUFFER_INFO), 1);
	DWORD size = 2;
	WORD tmp;
	DWORD  ret;
	int x, y, i = 0, j;
	SetConsoleOutputCP(65001);
	GetConsoleScreenBufferInfo(Handle, ScreenInfo);
	
	while(1) {
		for(x = 0; x < 32; x++) {
			for (y = 0; y < 16; y++) {
				
				COORD t = { x*2, y };
				
				tmp = (i % 0xF) << 4;
				FillConsoleOutputCharacter(Handle, (TCHAR) '█', size, t, &ret);
				FillConsoleOutputAttribute(Handle, tmp, size, t, &ret);
				if (ret == 0) {
					return 0;
				}
				
			}
		}
		i++;
		Sleep(33);
		COORD t2 = { 0, y + 1 };
		SetConsoleCursorPosition(Handle, t2);
		j = getch_noblock();
		if (j > 0) {
			i = j;
		}
	}

	 

	printf("Testing");
	CloseHandle(Handle);
	return 0;
}