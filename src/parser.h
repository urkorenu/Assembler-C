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

#define SOURCE_REGISTER 5
#define DESTINATION_REGISTER 2

#define DIRECT_ADDRESS 1
#define INDEX_ADDRESS 2
#define REGISTER_ADDRESS 3

struct assembler_data {
    struct linked_list* errors;
    struct linked_list* object_list;
    struct binary_tree* symbol_table;
    struct binary_tree* macro_tree;
    struct files* as_files;
    int ic;
    int dc;
};

extern const char ASSEMBLER_MEM_ERR[];

#define to_void_ptr(val) ((void*)(&(val)))

extern struct assembler_data*
assembler_alloc(void);

extern void
assembler_free(struct assembler_data *asm);

extern struct assembler_data
assembler_init(void);

void 
assembler_reset(struct assembler_data *asm);

extern int
add_bits(int source, int data, int location);

extern int
parse_first_phase(struct assembler_data* host, FILE* source_file, struct files *as_files);

extern void
parse_pre_processor(FILE* file, void* host, FILE* new_file);

#endif /*PARSER_H*/
