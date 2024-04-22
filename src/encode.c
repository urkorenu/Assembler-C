#include "encode.h"
#include "bucket.h"
#include "error.h"
#include "io.h"
#include "linked_list.h"
#include <ctype.h>
#include <string.h>

#define REGISTER_CODE_FMT "r%1d"

/* Add bits to an in and specific location */
int
add_bits(void* source, int data, int location)
{
    int source_int = ((int*)source)[0];
    int temp = data << location;
    return source_int | temp;
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
encode_string(struct assembler_data* assembler, char* line, int line_count)
{
    int idx, len;
    char* string;
    char tmp_word[MAXWORD];
    struct linked_list* last_node;

    if ((len = get_string(line, &string)) == -1) {
        print_in_error(MISSING_QUOTES, line_count, NULL);
        return;
    }

    idx = len;
    string += 1;

    get_word(string, &idx, tmp_word);
    if (tmp_word[0]) {
        print_in_error(EXTRA_TEXT, line_count, NULL);
        return;
    }

    for (idx = 0; idx < len - 1; idx++) {
        insert_ll_node(assembler->object_list, int_to_voidp((int)string[idx]));
        assembler->data_c++;
        assembler->ic++;
    }

    /* last word of string should  be 0 */
    last_node = insert_ll_node(assembler->object_list, 0);
    last_node->state = DATA_SET;
    assembler->data_c++;
    assembler->ic++;
}

/* Encode data */
void
encode_data(struct assembler_data* assembler, const char* line, int line_count)
{

    int idx = 0;
    int temp = 0;
    int found_comma;
    char word[MAXWORD];
    struct bucket* temp_data;
    get_word(line, &idx, word);
    get_word(line, &idx, word);

    while (word[0]) {
        get_word(line, &idx, word);
        if (is_starting_with_x(word, COMMA))
            print_in_error(EXTRA_COMMAS, line_count, NULL);
        if (is_ends_with_x(word, COMMA)) {
            found_comma = 1;
            remove_last_char(word);
        }
        if ((temp = atoi(word))) {
            insert_ll_node(assembler->object_list, int_to_voidp(temp));
            assembler->data_c++;
            assembler->ic++;
        } else {
            if ((temp_data = get_data_by_key(assembler->symbol_table, word))) {
                if (strcmp(temp_data->data, MDEFINE) == 0) {
                    if ((temp = atoi(temp_data->key))) {
                        insert_ll_node(assembler->object_list,
                                       int_to_voidp(temp));
                        assembler->data_c++;
                        assembler->ic++;
                    } else {
                        print_in_error(
                          INVALID_DATA, line_count, temp_data->key);
                    }
                } else {
                    print_in_error(NOT_DEFINED, line_count, temp_data->data);
                }
            } else {
                return;
            }
        }

        if (!found_comma) {
            get_word(line, &idx, word);
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
        code |= add_bits(
          temp_node->data, get_register_code(register_str), bit_location);
        set_data_int(temp_node, code);
    }
    code |= add_bits(source_code->data, REGISTER_ADDRESS, operand_location);
    set_data_int(source_code, code);
    if (!found_register) {
        insert_ll_node(assembler->object_list, int_to_voidp(reg_code));
        assembler->ic++;
        assembler->instruction_c++;
    }
}

void
encode_direct(struct assembler_data* assembler,
              struct line_data* inst,
              struct linked_list* source_code,
              int source,
              int line_count)
{
    int temp = 0;
    struct bucket* temp_data;
    char* val_str = inst->destination;

    if (source) {
        val_str = inst->source;
    }

    if (!val_str[1]) {
        print_in_error(INVALID_DIRECT, line_count, val_str);
        return;
    }
    if ((temp = atoi(val_str + 1))) {
        temp = temp << 2;
        insert_ll_node(assembler->object_list, int_to_voidp(temp));
        assembler->instruction_c++;
        assembler->ic++;
    } else {

        if ((temp_data =
               get_data_by_key(assembler->symbol_table, val_str + 1))) {
            if (strcmp(temp_data->data, MDEFINE) == 0) {
                if ((temp = atoi(temp_data->key))) {
                    temp = temp << 2;
                    insert_ll_node(assembler->object_list, int_to_voidp(temp));
                    assembler->instruction_c++;
                    assembler->ic++;
                } else
                    print_in_error(INVALID_DATA, line_count, temp_data->data);
            } else
                print_in_error(SYMBOL_NOT_FOUND, line_count, val_str + 1);
        } else
            print_in_error(SYMBOL_NOT_FOUND, line_count, val_str + 1);
    }
}

void
encode_index(struct assembler_data* assembler,
             struct line_data* inst,
             struct linked_list* source_code,
             int source,
             char* index,
             int line_count)
{
    struct bucket* temp_data;
    int operand_location = DESTINATION_OPERAND;
    int temp;
    int code;

    if (source) {
        operand_location = SOURCE_OPERAND;
    }
    code = add_bits(source_code->data, INDEX_ADDRESS, operand_location);
    set_bucket_ic(source_code->data, code);

    insert_ll_node(assembler->object_list, 0);
    assembler->instruction_c++;
    assembler->ic++;
    temp = atoi(index);
    if (temp || !(strcmp(index, "0"))) {
        temp = temp << 2;
        insert_ll_node(assembler->object_list, int_to_voidp(temp));
        assembler->instruction_c++;
        assembler->ic++;
    } else {
        if ((temp_data = get_data_by_key(assembler->symbol_table, index))) {
            if (strcmp(temp_data->data, MDEFINE) == 0) {
                if ((temp = atoi(temp_data->key)) && temp >= 0) {
                    temp = temp << 2;

                    insert_ll_node(assembler->object_list, int_to_voidp(temp));
                    assembler->instruction_c++;
                    assembler->ic++;
                } else {
                    print_in_error(INVALID_DATA, line_count, temp_data->key);
                }
            } else {
                print_in_error(SYMBOL_NOT_FOUND, line_count, index);
            }
        } else {
            print_in_error(SYMBOL_NOT_FOUND, line_count, index);
        }
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
    set_data_int(source_code, code);
    insert_ll_node(assembler->object_list, 0);
    assembler->instruction_c++;
    assembler->ic++;
}

void
encode_operand(struct assembler_data* assembler,
               struct line_data* inst,
               struct linked_list* source_code,
               char* operand,
               int is_source,
               int* found_reg,
               int line_count)
{
    if (is_register(operand, line_count)) {
        encode_register(assembler, inst, (*found_reg), source_code, is_source);
        (*found_reg) = 1;
    } else if (is_starting_with_x(operand, HASH)) {
        encode_direct(assembler, inst, source_code, is_source, line_count);
    } else {
        char* index = get_index(operand);
        if (index) {
            encode_index(
              assembler, inst, source_code, is_source, index, line_count);
            free(index);
        } else {
            encode_null(assembler, inst, source_code, is_source);
        }
    }
}
