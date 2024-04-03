#include "register.h"

#define register_code_fmt "r%1d"

int
get_register_code(char* reg)
{
    int code = 0;
    assert(sscanf(reg, register_code_fmt, &code) == 1);
    return code;
}

extern register_t
register_init(int code, operand_t operand)
{
    return (register_t) {
        .code=code,
        .offset=register_offset(operand),
        .operand=operand
    };
}
