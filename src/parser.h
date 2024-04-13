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

extern void
parse_pre_processor(FILE* file, void* host, FILE* new_file);

extern int
parse_line(struct assembler_data* assembler,
           char* line,
           struct line_data* inst);

extern int
line_to_bin_1st(struct assembler_data* assembler,
                char* line,
                struct line_data* inst);
#endif /*PARSER_H*/
