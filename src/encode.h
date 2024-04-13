#ifndef ENCODE_H
#define ENCODE_H

#include "assembler.h"
#include "includes.h"
#include "instruction.h"
#include "io.h"
#include "linked_list.h"
#include "parser.h"

extern int
add_bits(void * source, int data, int location);

extern int
get_register_code(const char* reg);

extern void
encode_string(struct assembler_data* assembler, const char* line);

extern void
encode_data(struct assembler_data* assembler, const char* line);

extern void
encode_register(struct assembler_data* assembler,
                struct line_data* inst,
                int found_register,
                struct linked_list* source_code,
                int source);

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
