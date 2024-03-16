#ifndef _IO_H
#define _IO_H
#include "includes.h"

#define MAXWORD 100
#define MAX_LEN 81

extern char*
get_line(char* line, FILE* file);

extern char*
get_word(char* line, int* idx);

#endif /*_IO_H*/
