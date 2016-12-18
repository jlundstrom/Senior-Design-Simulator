#include "input.h"
#include <windows.h>

int check_Char(char c) {
	return (GetKeyState(c)>>16) & 0x1;
}

void Input_init(void) {
	Input_Status = 0;
}

void Input_Poll(void) {
	if (check_Char('W')) {
		Input_Status |= UP_INPUT;
	} else {
		Input_Status &= ~UP_INPUT;
	}
	if (check_Char('S')) {
		Input_Status |= DOWN_INPUT;
	}
	else {
		Input_Status &= ~DOWN_INPUT;
	}
	if (check_Char('A')) {
		Input_Status |= LEFT_INPUT;
	}
	else {
		Input_Status &= ~LEFT_INPUT;
	}
	if (check_Char('D')) {
		Input_Status |= RIGHT_INPUT;
	}
	else {
		Input_Status &= ~RIGHT_INPUT;
	}
	if (check_Char('Q')) {
		Input_Status |= A_INPUT;
	}
	else {
		Input_Status &= ~A_INPUT;
	}
	if (check_Char('E')) {
		Input_Status |= B_INPUT;
	}
	else {
		Input_Status &= ~B_INPUT;
	}
	if (check_Char('H')) {
		Input_Status |= START_INPUT;
	}
	else {
		Input_Status &= ~START_INPUT;
	}
	if (check_Char('J')) {
		Input_Status |= SELECT_INPUT;
	}
	else {
		Input_Status &= ~SELECT_INPUT;
	}
}