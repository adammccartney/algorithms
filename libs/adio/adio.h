#ifndef ADIO_H
#define ADIO_H

#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

char* getLine(size_t size);
char* fgetLine(size_t size, FILE* fd);

#endif
