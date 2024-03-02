#ifndef _IO_H
#define _IO_H
#include "includes.h"

#define MAXWORD 80

extern char *get_line(char *line, FILE *file);

extern char *get_word(char *line ,char *delimiters);

extern char *modify_path(const char *path);

#endif /*_IO_H*/
