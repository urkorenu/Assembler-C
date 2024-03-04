#include "macro.h"
#include "io.h"
#include <stdio.h>

static struct macro *macro_alloc(void) {
    return (struct macro *)malloc(sizeof(struct macro));
}

struct macro *create_macro(struct macro **p, fpos_t pos, int lines) {
    *p = macro_alloc(); 
    if (*p != NULL) { 
        set_start(*p, pos);
        set_lines(*p, lines);
    }
    return *p;
}

void insert_macro(struct macro *p, FILE *file, FILE *new_file)
{
    char temp[MAXWORD];
    int i = 0;
    fsetpos(file, &p->start);
    while (i++ < p->lines )
    {
        get_line(temp, file);
        fprintf(new_file, "%s", temp);
    }
}


void free_macro(struct macro *p)
{
    free(p);
}

void reset_macro(struct macro *p)
{
    memset(p, 0, sizeof(struct macro));
}

void set_start(struct macro *macro, fpos_t start)
{
    macro->start = start;
}

void set_lines(struct macro *macro, int lines)
{
    macro->lines = lines;
}
