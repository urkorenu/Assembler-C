#ifndef PARSER_H
#define PARSER_H

#include "Errors.h"
#include "assembler.h"
#include "binary_tree.h"
#include "bucket.h"
#include "encode.h"
#include "files.h"
#include "includes.h"
#include "instruction.h"
#include "io.h"
#include "linked_list.h"
#include "macro.h"

#define CODE "code"
#define MDEFINE "mdefine"
#define DATA "data"
#define EXTERNAL "external"

#define COMMA ','
#define HASH '#'

#define SOURCE_OPERAND 4
#define DESTINATION_OPERAND 2

#define SOURCE_REGISTER 5
#define DESTINATION_REGISTER 2

#define DIRECT_ADDRESS 1
#define INDEX_ADDRESS 2
#define REGISTER_ADDRESS 3

#define to_void_ptr(val) ((void*)(&(val)))
/**
 * @brief Parses the file and operate the pre-processor into a file.
 * This function reads pre-processor directives from the given file and performs
   appropriate actions based on the directives encountered.
 * @param file Pointer to the input file.
 * @param host Pointer to the host data structure.
 * @param new_file Pointer to the output file.
 */

extern void
parse_pre_processor(struct assembler_data* assembler);

/**
 * @brief Searches for the index and return it.
 * This function searches for the index of the opening square bracket [ in the given word and returns that index.
 * @param word A pointer that points to the first character of the input string
 * @return An integer value, which represents the index of the opening square bracket [ in the input word.
   If the opening bracket is found, the function returns the index of that bracket.
   If the opening bracket is not found in the word, the function returns -1 to indicate its absence.
 */
extern char*
get_index(char* word);

/**
 * @brief Parses a line of assembly code, extracting information about symbols, instructions, and operands.
 * @param assembler A pointer to a data structure representing the assembler, 
   which contains information and tools for parsing assembly code.
 * @param line A pointer to a string representing the line of assembly code to be parsed.
 * @param inst A pointer to a data structure of type struct line_data,
   which contains information about the parsed line, including symbols, commands, and operands.
 * @return An integer value. 
  It returns 1 if the line of assembly code is successfully parsed without any errors,
  indicating that the line is valid. 
  If any errors are encountered during parsing, such as missing symbols, invalid commands, 
  or extraneous characters, 
  the function returns 0 to indicate that the line is not valid.
*/
extern int
parse_line(struct assembler_data* assembler,
           char* line,
           struct line_data* inst);

extern int
line_to_bin_1st(struct assembler_data* assembler,
                char* line,
                struct line_data* inst);

extern int
parse_define(struct assembler_data* assembler, char* line, int* idx);

extern int
parse_data_store_instruction(struct assembler_data* assembler,
                             char* line,
                             char* word,
                             int* reading_symbol,
                             int* reading_data,
                             char* symbol,
                             int* idx);

extern int
parse_extern(struct assembler_data* assembler, char* line, int* idx);

extern int
parse_instruction(struct assembler_data* assembler,
                  char* line,
                  int* idx,
                  int* reading_data,
                  int* reading_symbol,
                  char* symbol,
                  int* line_counter,
                  char* word);

#endif /*PARSER_H*/
