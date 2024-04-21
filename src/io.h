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

/**
 * @brief This function reads a line from a file, handling errors.
 * @param line Pointer to a character array where the line will be stored.
 * @param file File pointer to the input file.
 * @param result Pointer to the string read from the file.
 * @return Returns a pointer to the string read from the file (line) if successful,
   or NULL if there was an error or end of file was reached.
 */
extern char*
get_line(char* line, FILE* file);


 /**
 * @brief This function Extracts a word from a line of text.
 * @param line Pointer to the input string containing the line.
 * @param idx Pointer to an integer representing the current index in the input string.
 * @return Returns a pointer to the dynamically allocated character array containing the extracted word.
   If there are no more words or if an error occurs, it returns NULL.
 */   
extern char*
get_word(const char* line, int* idx);

 /**
 * @brief This function removes the last character from a string.
 * @param word Pointer to the string from which the last character will be removed.
 */  
extern void
remove_last_char(char* word);

 /**
 * @brief This function removes the first character from a string.
 * @param word Pointer to the string from which the first character will be removed.
 */ 
extern void
remove_first_char(char* word);

/**
 * @brief This function checks if a given word is a data store instruction.
 * @param word Pointer to the word being checked.
 * @return Returns 1 if the word is ".data" or ".string", indicating it is a data store instruction.
    Returns 0 otherwise, indicating it is not a data store instruction.
 */  
extern int
is_data_store_instruction(const char* word);

 /**
 * @brief This function checks if a given word is a symbol.
 * @param word Pointer to the word being checked.
 * @return Returns 1 if the word is a symbol.
    Returns 0 otherwise, is not a symbol.
 */   
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
