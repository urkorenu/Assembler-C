#ifndef PARSER_H
#define PARSER_H

#include "includes.h"

#define CODE "code"
#define MDEFINE "mdefine"
#define DATA "data"
#define EXTERNAL "external"

#define to_void_ptr(val) ((void *) (&(val)))

extern struct bucket *parse_first_phase(FILE *file, void *host, FILE *new_file);

extern void parse_pre_processor(FILE *file, void *host, FILE *new_file);

#endif /*PARSER_H*/
