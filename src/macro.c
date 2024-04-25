#include "include/macro.h"
#include "include/io.h"

static struct macro*
macro_alloc(void)
{
    return (struct macro*)malloc(sizeof(struct macro));
}

/**
 * @brief This function updates the starting position (start) of a struct macro
 object to the value provided as an argument to the function.
 * @param macro A pointer to a struct macro.
 * @param start Represents a file position (fpos_t).
   It holds the value that will be assigned to the start field of the struct
 macro object.
 */
static void
set_start(struct macro* macro, fpos_t start)
{
    macro->start_pos = start;
}

/**
 * @brief This function sets the number of lines in a macro.
 * @param macro A pointer to a struct macro object.
 */
static void
set_lines(struct macro* macro, int lines)
{
    macro->line_amount = lines;
}

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

void
insert_macro(struct macro* p, FILE* file, FILE* new_file)
{
    char line[MAXWORD];
    int i = 0;
    fsetpos(file, &p->start_pos);
    while (i++ < p->line_amount) {
        get_line(line, file);
        fprintf(new_file, "%s", line);
    }
}

void
free_macro(struct macro* p)
{
    free(p);
}

void
reset_macro(struct macro* p)
{
    memset(p, 0, sizeof(struct macro));
}
