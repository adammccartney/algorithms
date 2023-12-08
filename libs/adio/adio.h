#ifndef ADIO_H
#define ADIO_H

#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

/* Possibly free up TRUE and FALSE keywords if they have been defined by system */
#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

char* ad_getline(size_t size);
char* fgetLine(size_t size, FILE* fd);

#endif
