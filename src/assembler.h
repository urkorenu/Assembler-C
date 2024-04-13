#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "includes.h"

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

extern int
parse_first_phase(struct assembler_data* host, FILE* source_file);

extern struct assembler_data*
assembler_alloc(void);

extern void
assembler_free(struct assembler_data* assembler);

extern struct assembler_data
assembler_init(void);

void
assembler_reset(struct assembler_data* assembler);

#endif /* ASSEMBLER_H */
