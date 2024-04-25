#ifndef _MACROS_H
#define _MACROS_H

#include "includes.h"

struct macro {
    fpos_t start_pos; /*The position in the file where the macro definition starts*/
    int line_amount;  /*The number of lines in the macro definition.*/
};

/**
 * @brief This function creates a new macro structure and initializes it with the provided position and number of lines.
 * @param A Pointer to a pointer to a struct macro. 
 * @param pos Represents a file position.
 * @param lines Represents the number of lines in the macro
 * @return A pointer to the newly created struct macro.
 */
extern struct macro*
create_macro(struct macro** p, fpos_t pos, int lines);

/**
 * @brief This function reads the lines of a macro from a given file and inserts them into another file.
 * @param p A pointer to the macro structure that contains information about the macro to be inserted.
 * @param pos  A pointer to a file stream that used for reading lines from the input file that contains the macro.
 * @param new_file A pointer to a file stream that used for writing lines to the output file
   where the macro will be inserted.
 */
extern void
insert_macro(struct macro* p, FILE* file, FILE* new_file);

/**
 * @brief This function frees the memory allocated for a macro.
 * @param p A pointer to the memory allocated for a macro structure that needs to be freed.
 */
extern void
free_macro(struct macro* p);

/**
 * @brief This function resets the content of a macro set them to zero .
 * @param p pointer to a struct macro object or structure in memory,
   which will be reset to zero by the function.
 */
extern void
reset_macro(struct macro* p);

#endif /* _MACROS_H */
