#ifndef _IO_H
#define _IO_H
#include "includes.h"

#define MAXWORD 100
#define MAX_LEN 81
#define MAX_INDEX_LENGTH 4

extern char*
get_line(char* line, FILE* file);

extern char*
get_word(char* line, int* idx);


extern void
remove_last_char(char* word);


extern void
remove_first_char(char* word);


extern int
is_data_store_instruction(const char* word);


extern int
is_symbol(const char* word);


extern int
is_ended_with_x(const char* word, const char x);


extern int
is_starting_with_x(const char* word, const char x);


extern int
is_e_instruction(const char* word);

extern int
is_register(const char* word);

extern char*
mystrdup(char* s);

#endif /*_IO_H*/
