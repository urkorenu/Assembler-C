#include "include/macro.h"
#include "include/io.h"

/* Function to allocate memory for a macro */
static struct macro*
macro_alloc(void)
{
    return (struct macro*)malloc(sizeof(struct macro));
}

/* Creates a new macro with the given position and number of lines */
struct macro*
create_macro(struct macro** p, fpos_t pos, int lines)
{
    *p = macro_alloc();
    if (*p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    set_start(*p, pos);
    set_lines(*p, lines);
    return *p;
}

/* Inserts the content of a macro from a file to another file */
void
insert_macro(struct macro* p, FILE* file, FILE* new_file)
{
    char line[MAXWORD];
    int i = 0;
    fsetpos(file, &p->start);
    while (i++ < p->lines) {
        get_line(line, file);
        fprintf(new_file, "%s", line);
    }
}

/* Frees the memory allocated for a macro */
void
free_macro(struct macro* p)
{
    free(p);
}

/* Resets the content of a macro */
void
reset_macro(struct macro* p)
{
    memset(p, 0, sizeof(struct macro));
}

/* Sets the start position of a macro */
void
set_start(struct macro* macro, fpos_t start)
{
    macro->start = start;
}

/* Sets the number of lines in a macro */
void
set_lines(struct macro* macro, int lines)
{
    macro->lines = lines;
}
