#ifndef _MACROS_H
#define _MACROS_H

#include "includes.h"
#include "bucket.h"
#include <stdio.h>

struct macro {
    fpos_t start;
    int lines;
};

extern struct macro *create_macro(struct macro **p, fpos_t pos,
                                            int lines);
extern void insert_macro(struct macro *p, FILE *file, FILE *new_file);

extern void free_macro(struct macro *p);

extern void reset_macro(struct macro *p);

extern void set_start(struct macro *macro, fpos_t start);

extern void set_lines(struct macro *macro, int lines);

#endif /* _MACROS_H */
