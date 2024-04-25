#ifndef ENCODE_H
#define ENCODE_H

#include "assembler.h"
#include "includes.h"
#include "instruction.h"
#include "io.h"
#include "linked_list.h"

#define REGISTER_CODE_FMT "r%1d"

/*The file contain all functions for encoding bits in the program*/

/**
 * @brief This function adds bits to a number in a certain position.
 * The function takes integer type number, which is the number to which we want
 * to add bits, integer type number the bits we want to add, and integer type
 * number the position where we want to add the bits. The function performs one
 * iteration unless requested otherwise.
 * @param source: An integer type number to which we want to add bits.
 * @param data: An integer type number that represents the number we want to
 * add.
 * @param location: A variable of type int that symbolizes the position where we
 * want to add the bits.
 * @return An extern integer indicatingthe the number after adding the bits.
 */
extern int
add_bits(void* source, int data, int location);

/**
 * @brief This function extracts and returns the code associated with a register
 from its name string.
 * The function get a pointer to a constant character string (const char*).
 * @param reg: Pointer to a constant character string representing a register
 name of the register from which the code is to be extracted.

 * @return An integer indicatingthe the extracted integer code.
 * If the parsing fails, the program terminates.

 */
extern int
get_register_code(const char* reg);

/**
 * @brief This function encodes a string word into a linked list and converts
 * each character to its ascii representation
 * @param assembler: Pointer to a struct assembler_data.
 * @param line: pointer to a constant character string.
 * @param line_count: integer that represent the current line of the assembly file.
 */
extern void
encode_string(struct assembler_data* assembler, char* line, int line_count);

/**
 * @brief This function encodes data from the input string according to the
 assembler instructions and adds it to a linked list in the structure of the
 assembler Errors are handled by returning from the function with appropriate
 error messages or conditions. The function uses various helper functions to
 parse the string.
 * @param assembler: Pointer to a struct assembler_data.
 * @param line: and a pointer to a constant character string.
 * @param line_count: integer that represent the current line of the assembly file.
 */
extern void
encode_data(struct assembler_data* assembler, const char* line, int line_count);

/**
 * @brief This function Encodes register operands in assembly instructions.
 * @param assembler: Pointer to a struct assembler_data.
 * @param inst: A pointer to a struct line_data.
 * @param found_register An integer flag indicating whether a register operand
 was found in the instruction.
 * @param source_code A pointer to a struct linked_list
    representing the source code data associated with the instruction.
 * @param source An integer flag indicating whether the register operand is from
 the source or destination of the instruction.
 */
extern void
encode_register(struct assembler_data* assembler,
                struct line_data* inst,
                int found_register,
                struct linked_list* source_code,
                int source);

/**
 * @brief Encodes direct addressing operands in assembly instructions
 * This function Determines whether the operand is from the source or
 * destination of the instruction. Parses and converts the operand value to an
 * integer, shifting it appropriately. Inserts the encoded value into the
 * assembler's object list, updating the instruction counter and object list
 * count. Handles errors related to invalid values, undefined symbols, or unknown
 * data.
 * @param assembler: Pointer to a struct assembler_data.
 * @param inst: A pointer to a struct line_data.
 * @param source_code A pointer to a struct linked_list
 *  representing the source code data associated with the instruction
 * @param source An integer flag indicating whether the operand is from the
 * source or destination of the instruction.
 * @param line_count: integer that represent the current line of the assembly file.
 */
extern void
encode_direct(struct assembler_data* assembler,
              struct line_data* inst,
              struct linked_list* source_code,
              int source,
              int line_count);

/**
 * @brief Encodes indexed addressing operands in assembly instructions.
   This function determines whether the operand is from the source or
 destination of the instruction. Encodes the source code data (such as opcode or
 address) with the index address. Inserts a placeholder value into the
 assembler's object list for later modification during the second phase. Parses
 and converts the index value to an integer, shifting it appropriately. Inserts
 the encoded index value into the assembler's object list, updating the
 instruction counter and object list count. Handles errors related to invalid
 values, undefined symbols, or unknown indices.
 * @param assembler: Pointer to a struct assembler_data.
 * @param inst: A pointer to a struct line_data.
 * @param source_code A pointer to a struct linked_list
   representing the source code data associated with the instruction
 * @param source An integer flag indicating whether the operand is from the
 source or destination of the instruction.
 * @param index A pointer to a character array representing the index value
 extracted from the instruction.
 * @param line_count: integer that represent the current line of the assembly file.
 */
extern void
encode_index(struct assembler_data* assembler,
             struct line_data* inst,
             struct linked_list* source_code,
             int source,
             char* index,
             int line_count);

/**
 * @brief Encodes null (empty) operands in assembly instructions.
   This function Determines whether the operand is from the source or
 destination of the instruction. Encodes the source code data (such as opcode or
 address) with a direct address value. Sets the encoded value into the source
 code data. Inserts a placeholder value (0) into the assembler's object list for
 later modification. Updates the instruction counter and object list count.
 * @param assembler: Pointer to a struct assembler_data.
 * @param inst: A pointer to a struct line_data.
 * @param source_code A pointer to a struct linked_list
   representing the source code data associated with the instruction
 * @param source An integer flag indicating whether the operand is from the
 source or destination of the instruction.
 */
extern void
encode_null(struct assembler_data* assembler,
            struct line_data* inst,
            struct linked_list* source_code,
            int source);

/**
 * @brief Encodes the operand of an assembly instruction based on its type.
   This function determines whether the operand is a register, immediate value,
 indexed addressing, or null. Calls corresponding encoding functions based on
 the operand type. Manages the state of found registers during encoding.
 * @param assembler: Pointer to a struct assembler_data.
 * @param inst: A pointer to a struct line_data.
 * @param source_code A pointer to a struct linked_list
   representing the source code data associated with the instruction
 * @param operand A character pointer representing the operand of the
 instruction that needs to be encoded.
 * @param is_source An integer flag indicating whether the operand is from the
 source or destination of the instruction.
 * @param found_reg A pointer to an integer used to track whether a register
 operand has been found during encoding.
 * @param line_count: integer that represent the current line of the assembly file.
 */
extern void
encode_operand(struct assembler_data* assembler,
               struct line_data* inst,
               struct linked_list* source_code,
               char* operand,
               int is_source,
               int* found_reg,
               int line_count);

#endif /* ENCODE_H*/
