#include "simpleMenu.h"

bool showSimpleMenu()
{
    printf("Simple Menu\n");
    printf("Press + to exit\n");
    printf("Press A to FILE_TRANSFER_HTTP_TEMPORALY\n");
    printf("Press B to FILE_TRANSFER_HTTP(1)\n");

    while (appletMainLoop())
    {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Up)
            printf("Up pressed\n");
        if (kDown & HidNpadButton_Down)
            printf("Down pressed\n");
        if (kDown & HidNpadButton_Left)
            printf("Left pressed\n");
        if (kDown & HidNpadButton_Right)
            printf("Right pressed\n");
        if (kDown & HidNpadButton_A)
        {
            printf("A pressed\n");
            if (FILE_TRANSFER_HTTP_TEMPORALY() == false)
            {
                if (FILE_TRANSFER_HTTP(2) == true)
                {
                    return true;
                }
            }
        }
        if (kDown & HidNpadButton_B)
        {
            printf("B pressed\n");
            FILE_TRANSFER_HTTP(1);
        }
        if (kDown & HidNpadButton_X)
            printf("X pressed\n");
        if (kDown & HidNpadButton_Y)
            printf("Y pressed\n");

        if (kDown & HidNpadButton_Plus)
            return true;

        consoleUpdate(NULL);
    }
    return true;
}