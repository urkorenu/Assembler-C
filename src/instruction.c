#include "instruction.h"
#include "includes.h"

struct line_data*
init_instruction(struct line_data* p)
{
    p = (struct line_data*)malloc(sizeof(struct line_data));
    return p;
}

int
get_instruction(struct line_data* p, char* word)
{
    if (!word)
        return 0;
    if (strcmp(word, "mov") == 0) {
        p->code = 0;
        p->args = 2;
    } else if (strcmp(word, "cmp") == 0) {
        p->code = 1;
        p->args = 2;
    } else if (strcmp(word, "add") == 0) {
        p->code = 2;
        p->args = 2;
    } else if (strcmp(word, "sub") == 0) {
        p->code = 3;
        p->args = 2;
    } else if (strcmp(word, "not") == 0) {
        p->code = 4;
        p->args = 1;
    } else if (strcmp(word, "clr") == 0) {
        p->code = 5;
        p->args = 1;
    } else if (strcmp(word, "lea") == 0) {
        p->code = 6;
        p->args = 2;
    } else if (strcmp(word, "inc") == 0) {
        p->code = 7;
        p->args = 1;
    } else if (strcmp(word, "dec") == 0) {
        p->code = 8;
        p->args = 1;
    } else if (strcmp(word, "jmp") == 0) {
        p->code = 9;
        p->args = 1;
    } else if (strcmp(word, "bne") == 0) {
        p->code = 10;
        p->args = 1;
    } else if (strcmp(word, "red") == 0) {
        p->code = 11;
        p->args = 1;
    } else if (strcmp(word, "prn") == 0) {
        p->code = 12;
        p->args = 1;
    } else if (strcmp(word, "jsr") == 0) {
        p->code = 13;
        p->args = 1;
    } else if (strcmp(word, "rts") == 0) {
        p->code = 14;
        p->args = 0;
    } else if (strcmp(word, "hlt") == 0) {
        p->code = 15;
        p->args = 0;
    }
    if (p->code > 0 || p->args > 0)
        return 1;
    return 0;
}
