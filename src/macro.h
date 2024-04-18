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
 * @param pos Represents a file position, typically used for tracking positions in files.
 * @param lines Represents the number of lines in the macro
 * @return a pointer to the newly created struct macro.
 */
extern struct macro*
create_macro(struct macro** p, fpos_t pos, int lines);

extern void
insert_macro(struct macro* p, FILE* file, FILE* new_file);

extern void
free_macro(struct macro* p);

extern void
reset_macro(struct macro* p);

extern void
set_start(struct macro* macro, fpos_t start);

extern void
set_lines(struct macro* macro, int lines);

#endif /* _MACROS_H */
