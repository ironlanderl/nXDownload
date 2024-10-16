#pragma once

#ifndef _MENUCUI_H_
#define _MENUCUI_H_

#include <stdio.h>
#include <switch.h>
#include <stdbool.h>// bool: 1 == true; 0 == false;
#define HALF_SCREEN 40

// Define to count nb element in char **
#define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))

// Gamepad state
extern PadState pad;

/* Structures */
struct V {
  short int half;
  short int half_length;
  short int final_length;
};

extern struct V var;

struct menu {
	char *exit;
	short int n;
	short int m;
};

extern struct menu initial;

/* Prototypes */
void menu_options(void);
void title(char *str);
bool menu_main(void);
bool functionExit(void);

#endif
