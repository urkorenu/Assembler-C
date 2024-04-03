#ifndef ENCODE_H
#define ENCODE_H

#include "binary_tree.h"
#include "instruction.h"
#include "linked_list.h"
#include "operand.h"
#include "parser.h"
#include "register.h"

typedef size_t bytecode_t;

extern void
encode_string(struct assembler_data* assembler, char* line);

extern void
encode_data(struct assembler_data* assembler, char* line);

extern void
encode_register(struct assembler_data* assembler,
                struct line_data* input,
                int found_register,
                struct linked_list* output,
                operand_t operand);

extern void
encode_direct(struct assembler_data* assembler,
              struct line_data* inst,
              struct linked_list* source_code,
              int source);

extern void
encode_index(struct assembler_data* assembler,
             struct line_data* inst,
             struct linked_list* source_code,
             int source,
             char* index);

extern void
encode_null(struct assembler_data* assembler,
            struct line_data* inst,
            struct linked_list* source_code,
            int source);

#endif /* ENCODE_H*/
