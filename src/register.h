#ifndef REGISTER_H_
#define REGISTER_H_

#include "includes.h"
#include "operand.h"

#define REGISTER_WIDTH (3)
#define register_offset(operand) (\
    (\
        ((int)(operand))\
        / (REGISTER_WIDTH)\
    )\
    + ((int)(operand))\
)

typedef struct register_s {
    int code;
    int offset;
    operand_t operand;
} register_t;

extern int
get_register_code(char* reg);

extern register_t
register_init(int code, operand_t operand);

#endif /* REGISTER_H_ */
