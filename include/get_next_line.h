#pragma once

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

int get_next_line(int const fd, char **line);

