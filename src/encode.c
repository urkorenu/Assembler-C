#include "encode.h"
#include "io.h"
#include "linked_list.h"
#include "parser.h"

#define REGISTER_CODE_FMT "r%1d"

/* Add bits to an in and specific location */
int
add_bits(int source, int data, int location)
{
    int temp = data << location;
    return source | temp;
}

/* Count the number of bits in an integer */
static int count_bits(int n) {
    int count = 0;

    while (n != 0) {
        count++;
        n >>= 1;
    }
    return count;
}

/* Get the code of a register from its string representation */
int
get_register_code(const char* reg)
{
    int code = 0;

    assert(sscanf(reg, REGISTER_CODE_FMT, &code) == 1);

    return code;
}

/* Encode string characters */
void
encode_string(struct assembler_data* assembler, const char* line)
{
    int i = 0;
    int idx = 0;
    char* word = NULL;
    int* idx_ptr = &idx;
    word = get_word(line, idx_ptr);
    word = get_word(line, idx_ptr);
    word = get_word(line, idx_ptr);

    for (i = 1; word[i] != '\"' && word[i] != '\0'; i++) {
        insert_ll_node(assembler->object_list, (int)word[i]);
        assembler->ic++;
    }
    /* last word of string should  be 0 */
    insert_ll_node(assembler->object_list, 0);
    assembler->ic++;
}

/* Encode data */
void
encode_data(struct assembler_data* assembler, const char* line)
{

    int idx = 0;
    int temp = 0;
    int found_comma;
    char* word = NULL;
    int* idx_ptr = &idx;
    struct bucket* temp_data;
    word = get_word(line, idx_ptr);
    word = get_word(line, idx_ptr);

    while ((word = get_word(line, idx_ptr))) {
        if (is_ended_with_x(word, COMMA)) {
            found_comma = 1;
            remove_last_char(word);
        }
        if ((temp = atoi(word))) {
            insert_ll_node(assembler->object_list, temp);
            assembler->ic++;
        } else {
            if ((temp_data = get_data_by_key(assembler->symbol_table, word))) {
                if (strcmp(temp_data->data, MDEFINE) == 0) {
                    if ((temp = atoi(temp_data->key))) {
                        insert_ll_node(assembler->object_list, temp);
                        assembler->ic++;
                    } else
                        ;
                    /* error - value error */
                } else
                    ;
                /* error - index is not defined */
            } else
                return;
            /* error - Unknown index*/
        } /* inst->source = word; */

        if (!found_comma) {
            word = get_word(line, idx_ptr);
            if (is_starting_with_x(word, COMMA)) {
                remove_first_char(word);
                if (word[0] != '0')
                    idx -= (strlen(word)) - 1;
            }
        }
    }
}

/* Encode register */
void
encode_register(struct assembler_data* assembler,
                struct line_data* inst,
                int found_register,
                struct linked_list* source_code,
                int source)
{
    int code = 0;
    int reg_code = 0;
    char* register_str = inst->destination;
    int bit_location = DESTINATION_REGISTER;
    int operand_location = DESTINATION_OPERAND;

    if (source) {
        bit_location = SOURCE_REGISTER;
        operand_location = SOURCE_OPERAND;
        register_str = inst->source;
    }

    reg_code = get_register_code(register_str) << bit_location;

    if (found_register) {
        struct linked_list* temp_node;
        temp_node = get_last_node(assembler->object_list);
        code |= add_bits(get_lnode_data(temp_node, int),
                         get_register_code(register_str),
                         bit_location);
        set_data(temp_node, code);
    }
    code |= add_bits(source_code->data, REGISTER_ADDRESS, operand_location);
    set_data(source_code, code);
    if (!found_register){
        insert_ll_node(assembler->object_list, reg_code);
        assembler->ic++;
    }
}


void
encode_direct(struct assembler_data* assembler,
              struct line_data* inst,
              struct linked_list* source_code,
              int source)
{
    int temp = 0;
    struct bucket* temp_data;
    char* val_str = inst->destination;

    if (source) {
        val_str = inst->source;
    }

    if ((temp = atoi(val_str + 1))) {
        temp = temp << 2;
        insert_ll_node(assembler->object_list, temp);
        assembler->ic++;
    } else {

        if ((temp_data =
               get_data_by_key(assembler->symbol_table, val_str +1))) {
            if (strcmp(temp_data->data, MDEFINE) == 0) {
                if ((temp = atoi(temp_data->key))) {
                    temp = temp << 2;
                    insert_ll_node(assembler->object_list, temp);
                    assembler->ic++;
                } else
                    ;
                /* error : value error */
            } else
                ;
            /* error : not a defined symbol */
        } else
            ;
        /* error : Unknown data */
    }
}

void
encode_index(struct assembler_data* assembler,
             struct line_data* inst,
             struct linked_list* source_code,
             int source,
             char* index)
{
    int code;
    struct bucket* temp_data;
    int operand_location = DESTINATION_OPERAND;

    if (source) {
        operand_location = SOURCE_OPERAND;
    }
    code = add_bits(source_code->data, INDEX_ADDRESS, operand_location);
    source_code->data = code;
    /* It should change later at 2nd phase */
    insert_ll_node(assembler->object_list, 0);
    assembler->ic++;
    int temp = 0;
    if ((temp = atoi(index)) && (temp >= 0)) {
        printf("%d\n", count_bits(temp)); 
        temp = temp << 2;
        insert_ll_node(assembler->object_list, temp);
        assembler->ic++;
    } else {
        if ((temp_data = get_data_by_key(assembler->symbol_table, index))) {
            if (strcmp(temp_data->data, MDEFINE) == 0) {
                if ((temp = atoi(temp_data->key)) && temp >= 0) {
                    temp = temp << 2;

                    insert_ll_node(assembler->object_list, temp);
                    assembler->ic++;
                } else
                    ;
                /* error - value error */
            } else
                ;
            /* error - index is not defined */
        } else
            ;
        /* error - Unknown index*/
    }
}
void
encode_null(struct assembler_data* assembler,
            struct line_data* inst,
            struct linked_list* source_code,
            int source)
{
    int code = 0;
    int operand_location = DESTINATION_OPERAND;

    if (source) {
        operand_location = SOURCE_OPERAND;
    }
    code = add_bits(source_code->data, DIRECT_ADDRESS, operand_location);
    source_code->data = code;
    insert_ll_node(assembler->object_list, 0);
    assembler->ic++;
}

