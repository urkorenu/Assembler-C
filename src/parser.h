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

extern char*
get_index(char* word);

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
