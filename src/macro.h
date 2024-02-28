#ifndef _MACROS_H
#define _MACROS_H

#include "includes.h"
#include "bucket.h"

struct macro {
    int start;
    int end;
};

extern struct macro *create_macro(struct macro **p, int start,
                                            int end);
extern void free_macro(struct macro *p);

extern void reset_macro(struct macro *p);

extern void set_start(struct macro *macro, int start);

extern void set_end(struct macro *macro, int end);

extern void set_file(struct macro *macro, char *file);

extern int get_start(struct macro *macro);

extern int get_end(struct macro *macro);

extern char *get_file(struct macro *macro);

#endif /* _MACROS_H */
