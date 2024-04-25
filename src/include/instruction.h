#ifndef INSTRUCTION_H
#define INSTRUCTION_H

/* This structure represents data associated with a line of code or an
 * instruction */
struct line_data {
    char* symbol; /* Stores the symbol associated with the instruction. */
    int code; /* Represents the operation to be performed by the instruction. */
    char* source;      /* Stores the source operand of the instruction. */
    char* destination; /* Stores the destination operand of the instruction.. */
    int args;     /* Stores the number of arguments or operands expected by the
                     instruction. */
    int is_valid; /* Indicates whether the instruction is valid or not. */
};

/**
 * @brief This function initializes an instruction structure.
 * @param p Represents the instruction structure that is being initialized.
 * @return Returns a pointer to the initialized line_data structure.
 */
extern struct line_data*
init_instruction(struct line_data* p);

/**
 * @brief This function get the instruction code and number of arguments from a
 word.
 * @param p Represents the instruction structure where the instruction code and
 number of arguments will be stored.
 * @param word Input word representing the mnemonic of the instruction.
 * @return Returns 1 if the instruction code and number of arguments were
 successfully assigned to the line_data structure, otherwise it returns 0.
 */
extern int
get_instruction(struct line_data* p, const char* word);

#endif /* INSTRUCTION_H */
