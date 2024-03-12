#ifndef INSTRUCTION_H
#define INSTRUCTION_H

struct instruction {

    int code;
    int args;
};

extern struct instruction*
init_instruction(struct instruction* p);

extern int
get_instruction(struct instruction* p, char* word);

#endif /* INSTRUCTION_H */
