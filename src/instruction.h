#ifndef INSTRUCTION_H
#define INSTRUCTION_H

struct line_data {
    char* symbol;
    int code;
    char* source;
    char* destination;
    int args;
    int is_valid;
};

extern struct line_data*
init_instruction(struct line_data* p);

extern int
get_instruction(struct line_data* p, const char* word);

#endif /* INSTRUCTION_H */
