#include "macro.h"
static struct macro *macro_alloc(void) {
    return (struct macro *)malloc(sizeof(struct macro));
}

struct macro *create_macro(struct macro **p, int start, int end) {
    *p = macro_alloc(); 
    printf("macro allocated\n");
    if (*p != NULL) { 
        set_start(*p, start);
        printf("int set\n");
        set_end(*p, end);
        printf("end set\n");
    }
    return *p;
}


void free_macro(struct macro *p)
{
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


int get_start(struct macro *macro)
{ 
    return macro->start;
}

int get_end(struct macro *macro)
{
    return macro->end;
}
