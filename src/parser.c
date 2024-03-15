#include "parser.h"
#include "binary_tree.h"
#include "bucket.h"
#include "includes.h"
#include "instruction.h"
#include "io.h"
#include "linked_list.h"
#include "macro.h"

static int
is_data_store_instruction(char* word)
{
    if (strcmp(word, ".data") == 0)
        return 1;
    else if (strcmp(word, ".string") == 0)
        return 1;
    return 0;
}

static int
is_symbol(char* word)
{
    int length = strlen(word);
    if (word[length - 1] == ':')
        return 1;
    return 0;
}

static int
is_ended_with_x(char* word, char x)
{
    int length = strlen(word);
    if (word[length - 1] == x)
        return 1;
    return 0;
}

static int
is_starting_with_x(char* word, char x)
{
    if (word[0] == x)
        return 1;
    return 0;
}

static int
is_e_instruction(char* word)
{
    if (strcmp(word, ".extern") == 0)
        return 1;
    else if (strcmp(word, ".entry") == 0)
        return 1;
    return 0;
}

void
parse_pre_processor(FILE* file, void* host, FILE* new_file)
{
    int line_count = 1;
    char line[MAXWORD];
    char* key = NULL;
    int idx = 0;
    int* idx_ptr = &idx;
    char* word = NULL;
    int reading_macro = 0;
    int start_idx;
    struct macro* temp = NULL;
    fpos_t temp_pos;

    while (get_line(line, file) != NULL) {
        while ((word = get_word(line, idx_ptr))) {
            if (!reading_macro) {
                if (strcmp(word, "mcr") == 0) {
                    reading_macro = 1;
                    key = get_word(line, idx_ptr);
                    start_idx = ++line_count;
                    fgetpos(file, &temp_pos);
                    break;
                } else {
                    temp = get_data_by_key(host, word);
                    if (temp) {
                        fgetpos(file, &temp_pos);
                        insert_macro(temp, file, new_file);
                        fsetpos(file, &temp_pos);
                        ++line_count;
                        break;
                    } else {
                        fprintf(new_file, "%s", line);
                        ++line_count;
                        break;
                    }
                }
            }

            else {
                if (strcmp(word, "endmcr") == 0) {
                    struct macro* macro = NULL;
                    macro =
                      create_macro(&macro, temp_pos, line_count - start_idx);
                    insert_node(host, key, macro);
                    reading_macro = 0;
                    break;
                } else {
                    line_count++;
                    break;
                }
            }
        }
        word = NULL;
        idx = 0;
        memset(line, 0, MAXWORD);
    }
}

void
remove_last_char(char* word)
{
    int size = strlen(word);
    word[size - 1] = '\0';
    return;
}

static void
remove_first_char(char* word)
{
    word++;
    return;
}

int
add_bits(int source, int data, int location)
{
    int temp = data << location;
    return source | temp;
}

static int
is_register(char* word)
{
    int len = strlen(word);
    if (len == 2 && word[0] == 'r' && isdigit(word[len - 1])) {
        int temp = word[len - 1] - '0';
        if (0 <= temp && temp <= 7)
            return 1;
    }
    return 0;
}

static int
get_index(char* word, char* index)
{
    int i;
    int j = 0;
    int len = strlen(word);
    int inside_square_brackets = 0;
    for (i = 0; i <= len; i++) {
        if (word[i] == '[')
            inside_square_brackets = 1;
        else if (inside_square_brackets) {
            if (word[i] == ']')
                return 1;
            index[j++] = word[i];
            word[i] = '0';
        }
    }
    return 0;
}
int
parse_line(struct assembler_data* assembler, char* line, struct line_data* inst)
{
    char* word = NULL;
    int idx = 0;
    int* idx_ptr = &idx;
    int found_comma;
    while ((word = get_word(line, idx_ptr))) {
        if (is_symbol(word)) {
            inst->symbol = word;
            word = get_word(line, idx_ptr);
        }
        if (get_instruction(inst, word)) {
            if (inst->args == 2) {
                word = get_word(line, idx_ptr);
                if (is_ended_with_x(word, COMMA)) {
                    found_comma = 1;
                    remove_last_char(word);
                    strcpy(inst->source, word);
                    /* inst->source = word; */
                } else {
                    strcpy(inst->source, word);
                }
                if (!found_comma) {
                    word = get_word(line, idx_ptr);
                    if (is_starting_with_x(word, COMMA)) {
                        remove_first_char(word);
                        if (word[0] != '0')
                            idx -= (strlen(word)) - 1;
                    } else {
                        inst->is_valid = 0;
                        return 0;
                        /* error : missing comma */
                    }
                }
            }
            if (inst->args >= 1) {
                word = get_word(line, idx_ptr);
                if (is_ended_with_x(word, COMMA)) {
                    inst->is_valid = 0;
                    return 0;
                    /* error - too many commas */
                }
                strcpy(inst->destination, word);
            }
            if ((word = get_word(line, idx_ptr))) {
                inst->is_valid = 0;
                return 0;
                /* error  - too much text */
            }

        } else {
            inst->is_valid = 0;
            /* error : not a valid command */
        }
    }
    return 1;
}

int
line_to_bin_1st(struct assembler_data* assembler,
                char* line,
                struct line_data* inst)
{
    int code = inst->code << 6;
    struct bucket* temp_data;
    int found_reg = 0;
    struct linked_list* source_code =
      insert_ll_node(assembler->object_list, &code);
    char* index = NULL;
    if (inst->source) {
        if (is_register(inst->source)) {
            int reg_code = strlen(inst->source);
            reg_code = (inst->source[reg_code - 1] - '0') << SOURCE_REGISTER;
            code = add_bits(code, REGISTER_ADDRESS, SOURCE_OPERAND);
            source_code->data = (to_void_ptr(code));
            insert_ll_node(assembler->object_list, to_void_ptr(reg_code));
            found_reg++;
        }
        if (is_starting_with_x(inst->source, HASH)) {
            inst->source++;
            int temp = 0;

            if ((temp = atoi(inst->source))) {
                temp = temp << 2;
                insert_ll_node(assembler->object_list,
                               to_void_ptr(inst->source));
            } else {

                if ((temp_data = get_data_by_key(assembler->symbol_table,
                                                 inst->source))) {
                    if (strcmp(temp_data->data, MDEFINE) == 0) {
                        if ((temp = atoi(temp_data->key))) {
                            temp = temp << 2;
                            insert_ll_node(assembler->object_list,
                                           to_void_ptr(temp));
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
        if (get_index(inst->source, index)) {
            code = add_bits(code, INDEX_ADDRESS, SOURCE_OPERAND);
            source_code->data = (to_void_ptr(code));
            insert_ll_node(assembler->object_list, NULL);
            int temp = 0;
            if ((temp = atoi(index))) {
                temp = temp << 2;
                insert_ll_node(assembler->object_list, to_void_ptr(temp));
            } else {
                if ((temp_data =
                       get_data_by_key(assembler->symbol_table, index))) {
                    if (strcmp(temp_data->data, MDEFINE) == 0) {
                        if ((temp = atoi(temp_data->key))) {
                            temp = temp << 2;

                            insert_ll_node(assembler->object_list,
                                           to_void_ptr(temp));
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
            /* if (found_reg) {
                struct linked_list* temp_node;
                reg_code = reg_code >> 3;
                temp_node = get_last_node(assembler->object_list);
                code = add_bits((int)temp_node->data, reg_code, shift_bits);
                temp_node->data = to_void_ptr(code);
                return NULL; */
        } else {
            code = add_bits(code, DIRECT_ADDRESS, SOURCE_OPERAND);
            source_code->data = (to_void_ptr(code));
            insert_ll_node(assembler->object_list, NULL);
        }
    }

    return 0;
}

struct bucket*
parse_first_phase(struct assembler_data* assembler, FILE* source_file)
{
    int dc = 100;
    int ic = 100;
    char line[MAXWORD];
    char* key = NULL;
    int idx = 0;
    int* idx_ptr = &idx;
    char* word = NULL;
    char* symbol = NULL;
    int reading_symbol = 0;
    struct bucket* error = NULL;
    char error_data[MAXWORD];
    struct bucket* symbol_data = NULL;
    struct line_data* inst = NULL;
    init_instruction(inst);

    while (get_line(line, source_file) != NULL) {
        word = get_word(line, idx_ptr);

        if (strcmp(word, ".define") == 0) {
            key = get_word(line, idx_ptr);
            if (!get_data_by_key(assembler->symbol_table, key)) {
                word = get_word(line, idx_ptr);
                if (strcmp(word, "=") == 0) {
                    word = get_word(line, idx_ptr);
                    create_bucket(symbol_data, word, MDEFINE);
                    /* maybe need conversion to int or else */
                    insert_node(assembler->symbol_table, key, symbol_data);
                    ++ic;
                } else {
                    strcpy(error_data, "invalid syntax");
                    /* maybe i dont need to create bucket for every
                     * error or should i create tree of error ?! */
                    create_bucket(error, key, error_data);
                }

            } else {
                strcpy(error_data, "define key is already initialized");
                create_bucket(error, key, error_data);
            }
        } else if (is_symbol(word)) {
            strcpy(symbol, word);
            word = get_word(line, idx_ptr);
            reading_symbol = 1;
        }

        if (is_data_store_instruction(word)) {
            if (reading_symbol) {
                if (!get_data_by_key(assembler->symbol_table, symbol)) {
                    create_bucket(symbol_data, DATA, to_void_ptr(dc));
                    dc++;
                    /* maybe need conversion to int or else */
                    insert_node(assembler->symbol_table, symbol, symbol_data);
                    /* process functions */
                } else {
                    strcpy(error_data, "symbol is already initialized");
                    create_bucket(error, key, error_data);
                }
            }
        }
        if (is_e_instruction(word)) {
            if (strcmp(word, ".extern") == 0) {
                key = get_word(line, idx_ptr);
                create_bucket(symbol_data, NULL, EXTERNAL);
                insert_node(assembler->symbol_table, key, symbol_data);
                ic++;
            }
        } else {
            if (reading_symbol) {
                if (!get_data_by_key(assembler->symbol_table, symbol)) {
                    create_bucket(symbol_data, CODE, to_void_ptr(dc));
                    ic++;
                    /* maybe need conversion to int or else */
                    insert_node(assembler->symbol_table, symbol, symbol_data);
                } else {
                    strcpy(error_data, "symbol is already initialized");
                    create_bucket(error, key, error_data);
                }
            }
            if (get_instruction(inst, word)) {
                ic += inst->args;
            }
            /* process commands */
        }
        word = NULL;
        symbol = NULL;
        idx = 0;
        memset(line, 0, MAXWORD);
        reading_symbol = 0;
    }
    return error;
}
