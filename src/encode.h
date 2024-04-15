#ifndef ENCODE_H
#define ENCODE_H

#include "includes.h"
#include "instruction.h"
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
add_bits(int source, int data, int location);

/**
 * @brief This function extracts an integer code from a register name string.
 *
 * The function Initializes an integer variable code to 0.
   Uses sscanf to parse the register name string according to a specified format (REGISTER_CODE_FMT)
   and store the parsed integer into the code variable.
 * Uses assert to ensure that the parsing was successful. If the parsing fails, the program terminates.
   Returns the extracted integer 
 
 * @param reg: Pointer to a constant character string representing a register name.
 
 * @return An integer indicatingthe the extracted integer code.
 * If the parsing fails, the program terminates.
 
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
