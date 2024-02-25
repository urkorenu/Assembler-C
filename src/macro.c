#include "macro.h"

static struct macro *macro_alloc(void)
{
    return (struct macro *)malloc(sizeof(struct macro));
}

struct macro *create_macro(struct macro *p, int start, int end, char *file)
{
    p = macro_alloc();
    set_start(p, start);
    set_end(p, end);
    set_file(p, file);
    return p;
} 

void free_macro(struct macro *p)
{
    free(p->file);
    free(p);
}

void reset_macro(struct macro *p)
{
    memset(p, 0, sizeof(struct macro));
}

void set_start(struct macro *macro, int start)
{
    macro->start = start;
}

void set_end(struct macro *macro, int end)
{
    macro->end = end;
}

void set_file(struct macro *macro, char *file)
{
    memcpy(macro->file,file, sizeof(file) +1);
}

int get_start(struct macro *macro)
{ 
    return macro->start;
}

int get_end(struct macro *macro)
{
    return macro->end;
}

char *get_file(struct macro *macro)
{
    return macro->file;
}
