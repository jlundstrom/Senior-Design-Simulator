#pragma once

#define UP_INPUT 0x01
#define DOWN_INPUT 0x02
#define LEFT_INPUT 0x04
#define RIGHT_INPUT 0x08
#define A_INPUT 0x10
#define B_INPUT 0x20
#define START_INPUT 0x40
#define SELECT_INPUT 0x80

unsigned __int8 Input_Status;

void Input_init(void);
void Input_Poll(void);