#ifndef _IO_H
#define _IO_H

#include "includes.h"

#define MAXWORD 81
#define MAX_INDEX_LENGTH 4

 /**
 * @brief This function opens a file with error handling for failure to open.
 * @param fp A pointer to a string containing the file path.
 * @param modes A pointer to a string containing the file opening modes.
 * @param f File pointer for the opened file.
 * @return Returns a  pointer to the opened file if successful, or NULL if the file couldn't be opened.
 */ 
extern FILE*
verbose_fopen(const char *fp, const char *modes);

extern char*
get_line(char* line, FILE* file);

extern char*
get_word(const char* line, int* idx);

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
mystrdup(const char* s);

extern void*
int_to_voidp(int data);

extern char*
remove_square_brackets(char* word);

extern void
clean_word(char* word);

#endif /*_IO_H*/
