#ifndef _MACROS_H
#define _MACROS_H

#include "bucket.h"
#include "includes.h"
#include <stdio.h>

struct macro {
    fpos_t start;
    int lines;
};

/**
 * @brief This function creates a new macro structure and initializes it with the provided position and number of lines.
 * @param p Pointer to a pointer to a struct macro. 
 * @param pos Represents a file position.
 * @param lines Represents the number of lines in the macro
 * @return a pointer to the newly created struct macro.
 */
extern struct macro*
create_macro(struct macro** p, fpos_t pos, int lines);

/**
 * @brief This function reads the lines of a macro from a given file and inserts them into another file.
 * @param p a pointer to the macro structure that contains information about the macro to be inserted.
 * @param pos  a pointer to a file stream that used for reading lines from the input file that contains the macro.
 * @param new_file a pointer to a file stream that used for writing lines to the output file
   where the macro will be inserted.
 */
extern void
insert_macro(struct macro* p, FILE* file, FILE* new_file);

/**
 * @brief This function frees the memory allocated for a macro.
 * @param p pointer to the memory allocated for a macro structure that needs to be freed.
 */
extern void
free_macro(struct macro* p);

extern void
reset_macro(struct macro* p);

extern void
set_start(struct macro* macro, fpos_t start);

extern void
set_lines(struct macro* macro, int lines);

#endif /* _MACROS_H */
