#ifndef _MACROS_H
#define _MACROS_H

#include "../includes.h"

struct macro_data {
    int start;
    int end;
    char *file;
};

extern void set_start(struct macro_data *macro, int start);

extern void set_end(struct macro_data *macro, int end);

extern void set_file(struct macro_data *macro, char *file);

extern int get_start(struct macro_data *macro);

extern int get_end(struct macro_data *macro);

extern char *get_file(struct macro_data *macro);

#endif /* _MACROS_H */
