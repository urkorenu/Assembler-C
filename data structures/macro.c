#include "macro.h"


void set_start(struct macro_data *macro, int start)
{
    macro->start = start;
}

void set_end(struct macro_data *macro, int end)
{
    macro->end = end;
}

void set_file(struct macro_data *macro, char *file)
{
    macro->file = file;
}

int get_start(struct macro_data *macro)
{ 
    return macro->start;
}

int get_end(struct macro_data *macro)
{
    return macro->end;
}

char *get_file(struct macro_data *macro)
{
    return macro->file;
}
