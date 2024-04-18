#ifndef ENCODE_H
#define ENCODE_H

#include "assembler.h"
#include "includes.h"
#include "instruction.h"
#include "io.h"
#include "linked_list.h"
#include "parser.h"

/*The file contain all functions for encoding bits in the program*/

/**
 * @brief This function adds bits to a number in a certain position
 *
 * The function takes integer type number, which is the number to which we want to add bits, 
   integer type number the bits we want to add, and integer type nuber the position where we want to add the bits

 * The function performs one iteration unless requested otherwise
 
 
 * @param source: An integer type number to which we want to add bits
 * @param data: An integer type number that represents the number we want to add
 * @param location: A variable of type int that symbolizes the position where we want to add the bits
 
 * @return An extern integer indicatingthe the number after adding the bits.
 */
extern int
add_bits(void * source, int data, int location);

/**
 * @brief This function extracts and returns the code associated with a register from its name string.
 * The function get a pointer to a constant character string (const char*).
 * @param reg: Pointer to a constant character string representing a register name of the register
   from which the code is to be extracted.
 
 * @return An integer indicatingthe the extracted integer code.
 * If the parsing fails, the program terminates.
 
 */
 
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
