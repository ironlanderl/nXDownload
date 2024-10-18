#include "simpleMenu.h"

void generate_random_str(char *str, size_t string_len)
{
    if (string_len & 1)
        string_len--;
    for (size_t i = 0; i < string_len; i += 2)
    {
        u8 tmp = 0;
        randomGet(&tmp, sizeof(tmp));
        snprintf(&str[i], 3, "%02X", tmp);
    }
}

void extract_filename_from_url(char *url, char *filename)
{
    char *last_slash = strrchr(url, '/');
    if (last_slash == NULL)
    {
        strcpy(filename, url);
    }
    else
    {
        strcpy(filename, last_slash + 1);
    }
}

bool showSimpleMenu()
{
    printf("Simple Menu\n");
    printf("Press + to exit\n");
    printf("Press A to start file transfer from keyboard\n");
    printf("Press B to start file transfer from input.txt\n");
    printf("Press X to request URL from socket\n");

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
        {
            printf("X pressed\n");
            consoleUpdate(NULL);

            char url[1024];

            if (get_string_from_remote(url))
            {
                printf("URL: %s\n", url);
                char filename[128];
                extract_filename_from_url(url, filename);

                printf("Downloading file to %s\n", filename);
                printf("Press A to continue\n");
                while (!(kDown & HidNpadButton_A))
                {
                    padUpdate(&pad);
                    kDown = padGetButtonsDown(&pad);
                    consoleUpdate(NULL);
                }

                downloadFile(url, filename);
            }

            consoleUpdate(NULL);
        }
        if (kDown & HidNpadButton_Y)
            printf("Y pressed\n");

        if (kDown & HidNpadButton_Plus)
            return true;

        consoleUpdate(NULL);
    }
    return true;
}