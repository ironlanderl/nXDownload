#include <stdio.h>
#include <string.h>
#include <switch.h>
#include <stdbool.h> // bool = 1 == true; 0 == false;
#include "download.h"
#include "menuCUI.h"
#include "helper.h"

struct V var;
struct menu initial;
PadState pad;

void title(char *str)
{
	var.half = strlen(str) / 2;
	var.half_length = var.half;
	var.final_length = HALF_SCREEN;

	for (; var.half <= var.half_length; var.half--)
	{
		var.final_length--;
		if (var.half <= 0)
			break;
	}

	printf("\x1b[3;%dH%s%s%s", var.final_length, CONSOLE_GREEN, str, CONSOLE_RESET);
	return;
}

bool functionExit(void)
{
	printf("\n\n%s%s%s", CONSOLE_GREEN, "Finish!\n", CONSOLE_RESET);
	printf("\npress [+] to exit");
	printf("\npress [-] to continue");

	while (appletMainLoop())
	{
		padUpdate(&pad);
		u64 kDown = padGetButtonsDown(&pad);

		if (kDown & HidNpadButton_Plus)
			return true;
		if (kDown & HidNpadButton_Minus)
			return false;
		consoleUpdate(NULL);
	}

	return true;
}

void menu_options(void)
{

	char *tiles[] = {
		"Update to latest beta nXDownload",
		"Download from input.txt",
		"Download from temporaly URL",
		"Download from tmp URL (with Username & Password)"};

	initial.m = 5;
	initial.exit = "Exit";

	for (initial.n = 0; initial.n < (short int)COUNT_OF(tiles); initial.n++)
	{
		printf("\x1b[%d;3H%s", initial.m, tiles[initial.n]);
		initial.m++;
	}

	initial.m = initial.m + 1;
	printf("\x1b[%d;3H%s", initial.m, initial.exit);

	return;
}

bool menu_main(void)
{

	consoleClear();
	title("nXDownload v1.1b");
	menu_options();
	userAppInit();

	int select = 5;
	short int bkp_n = initial.n + 5;
	short int bkp_m = initial.m;

	padInitializeDefault(&pad);

	while (appletMainLoop())
	{

		title("nXDownload v1.1b");
		menu_options();

		/* Look here for colored text >> https://switchbrew.github.io/libnx/console_8h.html */
		printf("\x1b[%d;1H%s>%s", select, CONSOLE_CYAN, CONSOLE_RESET);

		// printf("Pad pointer address: %p\n", &pad);

		padUpdate(&pad);
		u64 kDown = padGetButtonsDown(&pad);

		printf("Buttons: %lx\n", kDown);

		if (kDown & HidNpadButton_Up)
		{
			printf("\x1b[%d;1H ", select);
			select = select - 1;

			if (select < 5)
				select = bkp_m; // 4 there is nothing
			if (select == bkp_n)
				select--; // between char tiles and exit

			printf("\x1b[%d;1H%s>%s", select, CONSOLE_CYAN, CONSOLE_RESET);
		}

		if (kDown & HidNpadButton_Down)
		{
			printf("\x1b[%d;1H ", select);
			select = select + 1;

			if (select == bkp_n)
				select++; // select goes to exit
			if (select > bkp_m)
				select = 5; // over char exit

			printf("\x1b[%d;1H%s>%s", select, CONSOLE_CYAN, CONSOLE_RESET);
		}

		if (kDown & HidNpadButton_A)
		{
			if (select == 5)
			{
				if (nXDownloadUpdate() == true)
				{
					return true;
				}
				consoleClear();
			}
			else if (select == 6)
			{
				if (FILE_TRANSFER_HTTP(INPUT_TXT) == true)
				{
					return true;
				}
				consoleClear();
			}
			else if (select == 7)
			{
				if (FILE_TRANSFER_HTTP_TEMPORALY() == false)
				{
					if (FILE_TRANSFER_HTTP(TMPFILE_TXT) == true)
					{
						return true;
					}
				}
				consoleClear();
			}
			else if (select == 8)
			{
				if (inputUserOrPassword(USER) != true)
				{
					if (inputUserOrPassword(PASSWORD) != true)
					{
						if (FILE_TRANSFER_HTTP_TEMPORALY() == false)
						{
							if (FILE_TRANSFER_HTTP(TMPFILE_TXT) == true)
								return true;
						}
					}
				}
				consoleClear();
			}
			else if (select == 10)
				return true;
		}

		if (kDown & HidNpadButton_Plus)
		{
			return true;
		}

		printf("Reached the end of the loop\n");

		consoleUpdate(NULL);

		printf("End of the loop\n");
	}

	return true;
}
