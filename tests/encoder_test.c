/* -------- */
/* Includes */
/* -------- */

#include <stdio.h>
#define TEST_IMPLEMENTATION

#include "test.h"

/* ------- */
/* Defines */
/* ------- */

#define pprint_list(list) \
    do {\
        fprintf(stdout, "%s = [\n\t", #list);\
        ll_fprintf(list, stdout, ",\n\t");\
        fprintf(stdout, "\n]\n");\
    } while(0)
#define MAX_REG_CODE 8
#define MAX_REG_STRLEN 2

/* -------- */
/* Typedefs */
/* -------- */

typedef enum register_test_enum {
    TEST_SRC_REG,
    TEST_DST_REG,
    TEST_BOTH
} reg_test_t;

/* ------------------------- */
/* Private Variables/Methods */
/* ------------------------- */

static char src_reg[MAX_REG_STRLEN + 1] = {0};
static char dst_reg[MAX_REG_STRLEN + 1] = {0};

static char*
get_reg_str(char *reg, int rcode)
{
    int_checker_t checker = {
        .expected=MAX_REG_STRLEN,
        .actual=snprintf(reg, MAX_REG_STRLEN + 1, "r%0d", rcode),
    };
    int_checker_check(checker);
    return reg;
}


static struct line_data
init_line_data(int src_rcode, int dst_rcode)
{

    struct line_data data = {
        .source=get_reg_str(src_reg, src_rcode),
        .code=0,
        .args=0,
        .is_valid=1,
        .destination=get_reg_str(dst_reg, dst_rcode)
    };
    return data;
}

/* ---------------- */
/* Public API Tests */
/* ---------------- */

void test_get_register_code(void)
{
    int rcode = 0, n = MAX_REG_STRLEN;
    char reg[n + 1];

    for (rcode = 0; rcode < MAX_REG_CODE; rcode++) {
        get_register_code(get_reg_str(reg, rcode));
        fprintf(
            stdout, 
            "get_register_code(%0d) has successfully passed.\n", 
            rcode
        );
    }
}

void test_encode_register(reg_test_t test_kind)
{
    const int src_shift = 4; 
    const int dst_shift = 2;

    int rcode;
    int src_rcode;
    int dst_rcode;
    int both_rcodes[2];
    struct line_data data;
    struct assembler_data asm;
    int_checker_t src_checker;
    int_checker_t dst_checker;
    int_checker_t both_checker;
    struct linked_list *src_code;
    struct linked_list *dst_code;
    struct linked_list *both_code;

    asm = assembler_init();
    src_checker = default_checker;
    dst_checker = default_checker;
    both_checker = default_checker;


    for (rcode = 0; rcode < (MAX_REG_CODE * MAX_REG_CODE); rcode++) {
        src_rcode = rcode / MAX_REG_CODE;
        dst_rcode = rcode % MAX_REG_CODE;
        both_rcodes[0] = src_rcode;
        both_rcodes[1] = dst_rcode;
        data = init_line_data(src_rcode, dst_rcode);

        src_code = insert_ll_node(asm.object_list, 0);
        dst_code = insert_ll_node(asm.object_list, 0);
        both_code = insert_ll_node(asm.object_list, 0);

        pprint_list(src_code);
        pprint_list(dst_code);
        pprint_list(both_code);

        encode_register(&asm, &data, 0, src_code, 1);
        encode_register(&asm, &data, 0, dst_code, 0);
        encode_register(&asm, &data, 0, both_code, 1);
        encode_register(&asm, &data, 1, both_code, 0);

        pprint_list(src_code);
        pprint_list(dst_code);
        pprint_list(both_code);

        src_checker.input = &both_rcodes[0];
        dst_checker.input = &both_rcodes[1];
        both_checker.input = both_rcodes;

        src_checker.input_size = 1;
        dst_checker.input_size = 1;
        both_checker.input_size = 2;

        src_checker.expected = (0 | (src_rcode << src_shift));
        dst_checker.expected = (0 | (dst_rcode << dst_shift));
        both_checker.expected = (0 | src_checker.expected | dst_checker.expected);

        src_checker.actual = src_code->data;
        dst_checker.actual = dst_code->data;
        both_checker.actual = both_code->data;

        int_checker_check(src_checker);
        int_checker_check(dst_checker);
        int_checker_check(both_checker);

        assert(src_code->state == DATA_SET);
        assert(dst_code->state == DATA_SET);
        assert(both_code->state == DATA_SET);
    }
}

void test_encode_direct(void);

void test_encode_index(void);

void test_encode_null(void);

int
main(int argc, char** argv)
{
    test_get_register_code();
    test_encode_register(TEST_SRC_REG);
    test_encode_register(TEST_DST_REG);
    test_encode_register(TEST_BOTH);
    return 0;
}
