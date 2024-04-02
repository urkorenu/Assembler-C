#ifndef TEST_H_
#define TEST_H_

#include "includes.h"
#include "parser.h"
#include "encode.h"

#define int_checker_check(checker) _int_checker_check(#checker, checker)
#define print_int_checker(checker) _print_int_checker(#checker, checker)

typedef struct int_checker_s {
    int *input;
    int expected;
    int actual;
    size_t input_size;
} int_checker_t;

const int_checker_t default_checker = {0, 0, 0, 0};

extern void 
_int_checker_check(const char* name, int_checker_t checker);

extern void
_print_int_checker(const char* name, int_checker_t checker);


#endif /* TEST_H_ */

#ifdef TEST_IMPLEMENTATION

void 
_int_checker_check(const char* name, int_checker_t checker)
{
    _print_int_checker(name, checker);
    assert(checker.expected == checker.actual);
}

void
_print_int_checker(const char* name, int_checker_t checker)
{
    if (checker.expected == checker.actual)
        fprintf(stdout, "\n--------------------MATCH--------------------\n");
    else
        fprintf(stdout, "\n------------------MISSMATCH------------------\n");
    fprintf(stdout, "checker:   %s\n", name);

    fprintf(stdout, "inputs:    {");
    if (checker.input != NULL && checker.input_size) {
        size_t i;
        fprintf(stdout, "%d", checker.input[0]);
        for (i = 1; i < checker.input_size; i++)
            fprintf(stdout, ", %d", checker.input[i]);
    }
    else {
        fprintf(stdout, "(NULL / UNKNOWN)");
    }
    fprintf(stdout, "}\n");

    fprintf(stdout, "expected:  %0d\n", checker.expected);
    fprintf(stdout, "actual:    %0d\n", checker.actual);
    fprintf(stdout, "---------------------------------------------\n\n");
}

#endif
