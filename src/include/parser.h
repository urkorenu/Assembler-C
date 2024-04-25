#ifndef PARSER_H
#define PARSER_H

#include "error.h"
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

/* Define string literals representing different types of data. */
#define CODE "code"
#define MDEFINE "mdefine"
#define DATA "data"
#define EXTERNAL "external"

#define COMMA ',' /* Defines the character ',' */ 
#define HASH '#' /* Defines the character '#' */ 

/*These macros define constants representing the number of operands expected for source and destination respectively in an instruction.*/
#define SOURCE_OPERAND 4
#define DESTINATION_OPERAND 2

/* These macros define constants representing the number of registers expected for source and destination respectively in an instruction.*/
#define SOURCE_REGISTER 5
#define DESTINATION_REGISTER 2

/* These macros define constants representing different addressing modes used to specify the location of operands.*/
#define DIRECT_ADDRESS 1
#define INDEX_ADDRESS 2
#define REGISTER_ADDRESS 3

/*Preprocessor macro that casts a variable to a void pointer*/
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

/**
 * @brief Searches for the index and return it.
 * This function searches for the index of the opening square bracket [ in the given word and returns that index.
 * @param word A pointer that points to the first character of the input string
 * @return An integer value, which represents the index of the opening square bracket [ in the input word.
   If the opening bracket is found, the function returns the index of that bracket.
   If the opening bracket is not found in the word, the function returns -1 to indicate its absence.
 */
extern char*
get_index(char* word);

/**
 * @brief Parses a line of assembly code, extracting information about symbols, instructions, and operands.
 * @param assembler A pointer to a data structure representing the assembler, 
   which contains information and tools for parsing assembly code.
 * @param line A pointer to a string representing the line of assembly code to be parsed.
 * @param inst A pointer to a data structure of type struct line_data,
   which contains information about the parsed line, including symbols, commands, and operands.
 * @return An integer value. 
  It returns 1 if the line of assembly code is successfully parsed without any errors,
  indicating that the line is valid. 
  If any errors are encountered during parsing, such as missing symbols, invalid commands, 
  or extraneous characters, 
  the function returns 0 to indicate that the line is not valid.
*/
extern int
parse_line(struct assembler_data* assembler,
           char* line,
           struct line_data* inst,
           int line_count);

/**
 * @brief Converts the first pass of an assembly code line into binary format.
 * This function Calculates the opcode and inserts it into the object list.
   Encodes the source and destination operands based on their types (register, direct, index).
 * @param assembler A pointer to a structure (struct assembler_data) containing data and tools for assembling code.
   It is used to access assembler-specific information and functionalities.
 * @param line A pointer to a character array representing a line of assembly code. 
   This is the input line that needs to be converted into binary format.
 * @param inst A pointer to a structure (struct line_data)
   representing the parsed information of the assembly code line. 
   It contains details such as the opcode, symbol, source operand, and destination operand.
   @return An integer value, 0.
*/
extern int
line_to_bin_1st(struct assembler_data* assembler,
                char* line,
                struct line_data* inst);


/**
 * @brief Parses the .define directive in the assembly code.
 * This function Verifies the syntax of the .define directive.
   Checks if the symbol defined by the .define directive is already present in the symbol table.
 * @param assembler A pointer to a structure (struct assembler_data) containing data and tools for assembling code.
   It is used to access assembler-specific information and functionalities.
 * @param line A pointer to a character array representing a line of assembly code.
   This line typically contains the .define directive that needs to be parsed.
 * @param idx A pointer to an integer that represents the current index in the line being parsed.
   It is used to keep track of the position within the line while parsing
   @return Returns 0 if any errors are encountered during parsing, otherwise continues parsing.
*/
extern int
parse_define(struct assembler_data* assembler, char* line, int* idx, int line_count);

/**
 * @brief Parses the data store instruction in the assembly code.
 * This function handles the reading of symbols and data during the parsing process.
   Invokes functions to handle symbols and process data accordingly.
 * @param assembler A pointer to a structure (struct assembler_data) containing data and tools for assembling code.
   It provides access to assembler-specific information and functionalities.
 * @param line A pointer to a character array representing a line of assembly code.
   This line typically contains the data store instruction to be parsed.
 * @param word A pointer to a character array representing a word extracted from the assembly code line.
    It may contain a symbol or data value being parsed.
 * @param reading_symbol A pointer to an integer flag indicating whether the function 
    is currently reading a symbol in the assembly code line.
 * @param reading_data A pointer to an integer flag indicating whether the function
    is currently reading data in the assembly code line.
 * @param symbol A pointer to a character array representing a symbol extracted from the assembly code line.
    It is used when handling symbols during parsing.
 * @param idx A pointer to an integer representing the current index in the line being parsed.
    It is used to keep track of the position within the line while parsing.
   @return Returns an integer value. 
    It returns 1 after successful parsing of the data store instruction, indicating that the function has completed.
    It return 0 if any errors occur during the parsing, to indicate that the parsing process was unsuccessful.
*/
extern int
parse_data_store_instruction(struct assembler_data* assembler,
                             char* line,
                             char* word,
                             int* reading_symbol,
                             int* reading_data,
                             char* symbol,
                             int* idx,
                             int line_count);

/**
 * @brief Parses the .extern directive in the assembly code.
 * This function Verifies the syntax of the .extern directive.
   Inserts the symbol specified by the .extern directive into the symbol table with the appropriate type (EXTERNAL).
 * @param assembler A pointer to a structure (struct assembler_data) containing data and tools for assembling code. 
    It provides access to assembler-specific information and functionalities, such as the symbol table.
 * @param line A pointer to a character array representing a line of assembly code.
    This line typically contains the .extern directive to be parsed.
 * @param idx A pointer to an integer representing the current index in the line being parsed.
   It is used to keep track of the position within the line while parsing.
 * @param key A pointer to a character array representing the symbol specified by the .extern directive.
    It is extracted from the assembly code line and used to insert the symbol into the symbol table.
   @return Returns 1 if the directive is successfully parsed and the symbol is inserted into the symbol table
    Returns 0 if the analysis failed. If we encountered any errors during the analysis.
    */
extern int
parse_extern(struct assembler_data* assembler, char* line, int* idx, int line_count);

/**
 * @brief Parses an instruction in the assembly code.
 * This function Manages the reading of symbols and data during the parsing process.
   Initializes an instruction structure and a code bucket.
   Checks if the symbol associated with the instruction is already initialized.
   Sets the instruction counter for the code bucket.
   Parses the instruction line and converts it into binary format.
 * @param assembler containing data and tools for assembling code.
   It provides access to assembler-specific information and functionalities, 
   such as the symbol table and instruction counter.
 * @param line A pointer to a character array representing a line of assembly code.
    This line typically contains the instruction to be parsed.
 * @param idx A pointer to an integer representing the current index in the line being parsed.
   It is used to keep track of the position within the line while parsing.
 * @param reading_data A pointer to an integer flag indicating whether the function
    is currently reading data in the assembly code line.
    It is used to control the parsing process.
 * @param reading_symbol A pointer to an integer flag indicating whether the function 
    is currently reading a symbol in the assembly code line.
    It is used to control the parsing process.
 * @param symbol A pointer to a character array representing a symbol associated with the instruction. 
 * @param line_counter A pointer to an integer representing the current line number being processed.
    It is used for error reporting.
 * @param word A pointer to a character array representing a word extracted from the assembly code line.
    It may contain the opcode or operand of the instruction.
 * @param b A pointer to a structure (struct bucket) representing a code bucket associated with the instruction.
    It is used to store information about the instruction in the symbol table.
 * @param inst A pointer to a structure (struct line_data) representing the parsed information 
   of the assembly code instruction.
   @return Returns 1 if the directive is successfully parsed and the symbol is inserted into the symbol table
    Returns 0 if the analysis failed. If we encountered any errors during the analysis.
    */
extern int
parse_instruction(struct assembler_data* assembler,
                  char* line,
                  int* idx,
                  int reading_data,
                  int reading_symbol,
                  char* symbol,
                  int* line_counter,
                  char* word, 
                  int line_count);

/**
 * @brief This function processes each line of the assembly code,
   identifying symbols, data store instructions, externs, and entries.
 * @param assembler Pointer to the assembler data structure containing various information about the assembly process.
 * @param line The current line of assembly code being processed.
 * @param line_counter  Pointer to an integer representing the line number.
 * @param entry_list Pointer to a linked list storing entry points.
 * @param entry_flag Pointer to an integer flag indicating whether an entry point is encountered.
 * @param extern_list Pointer to a linked list storing external symbols.
 * @param extern_flag Pointer to an integer flag indicating whether an extern symbol is encountered.
 * @param last_unset_node Pointer to the last node in the object list where data is yet to be set.
 * @param node_ic Pointer to an integer representing the instruction counter.
 * @return Returns 1 if the processing of the line was successful, otherwise 0.
 */ 
extern int
process_line(struct assembler_data* assembler,
             char* line,
             int* line_counter,
             struct linked_list* entry_list,
             int* entry_flag,
             struct linked_list* extern_list,
             int* extern_flag,
             struct linked_list* last_unset_node,
             int* node_ic);

#endif /*PARSER_H*/
