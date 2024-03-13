#ifndef PARSER_H
#define PARSER_H

#include "binary_tree.h"
#include "files.h"
#include "includes.h"
#include "linked_list.h"

#define CODE "code"
#define MDEFINE "mdefine"
#define DATA "data"
#define EXTERNAL "external"

#define COMMA ','
#define HASH '#'

#define SOURCE_OPERAND 4
#define DESTINATION_OPERAND 2

struct assembler_data {
    struct linked_list* errors;
    struct linked_list* object_list;
    struct binary_tree* symbol_table;
    struct binary_tree* macro_tree;
    struct files* as_files;
    int ic;
    int dc;
};

#define to_void_ptr(val) ((void*)(&(val)))

extern struct bucket*
parse_first_phase(struct assembler_data* host, FILE* source_file);

extern void
parse_pre_processor(FILE* file, void* host, FILE* new_file);

#endif /*PARSER_H*/
