#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "includes.h"

struct assembler_data {
    struct linked_list* errors; /*Linked list that stores errors*/
    struct linked_list* object_list; /*Linked list  that stores assembled object code or data.*/
    struct binary_tree* symbol_table; /*Binary tree that stores symbols encountered during assembly along with their corresponding values or addresses.*/
    struct binary_tree* macro_tree; /*Binary tree that stores macros encountered during assembly.*/
    struct files* as_files; /*Struct files that contains paths to various files */
    int ic; /* Instruction Counter */
    int data_c; /* The count of data elements encountered during assembly.*/
    int instruction_c; /* The count of instructions encountered during assembly.*/

extern const char ASSEMBLER_MEM_ERR[];

 /**
 * @brief This function executes the first pass of the assembly file parsing and processing.
 * @param assembler Pointer to a struct assembler_data.
 * @return An integer indicating whether an error occurred during the first pass.
 *  If no error occurred, it returns 0.
 *  If an error occurred, it returns a non-zero value.
 */ 
extern int
parse_first_phase(struct assembler_data* host);

/**
 * Execute the second pass of the assembler.

* @brief This function executes the second pass of the assembler.
 It performs various tasks such as reading the processed input file, processing each line,
 checking for errors, handling labels and symbols, writing entries and externs to separate output files if they exist.
 It takes an assembler_data struct pointer as input, which contains information about the assembly process,
 such as the processed source file and symbol table.
 * @param assembler Pointer to a struct assembler_data.
 * @return Returns 0 if the second pass is executed successfully without errors, 1 otherwise.
 */
extern int
parse_second_phase(struct assembler_data* assembler);


 /**
 * @brief This function dynamically allocates memory for an assembler_data struct.
 * @param assembler Pointer to a struct assembler_data.
 * @return Returns NULL if memory allocation fails and it prints an error message,
   Otherwise, it returns a pointer to the allocated memory.
 */ 
extern struct assembler_data*
assembler_alloc(void);

/**
 * @brief This function allocates memory for an assembler_data struct, and set the pointer to NULL.
 * @param assembler Pointer to a struct assembler_data. 
 */ 
extern void
assembler_free(struct assembler_data* assembler);

 /**
 * @brief This function initializes a struct of type assembler_data.
 *  It creates new linked lists and binary trees for storing errors, object code, symbols, and macros.
 * @param path a string specifying the file path.
 * @return Returns a struct assembler_data object that is initialized with the provided file path.
 */ 
extern struct assembler_data
assembler_init(char* path);

#endif /* ASSEMBLER_H */
