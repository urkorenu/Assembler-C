#include "parser.h"
#include "binary_tree.h"
#include "bucket.h"
#include "includes.h"
#include "instruction.h"
#include "io.h"
#include "macro.h"
#include <cstdlib>
#include <stdlib.h>
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

int
add_bits(int source, int data, int location)
{
    int temp = data << location;
    return source & temp;
}

int
line_to_bin_1st(struct assembler_data* assembler,
                char* line,
                struct instruction* inst)
{
    int code = 0b00000000;
    code = inst->code << 6;
    int found_comma = 0;
    int idx = 0;
    int* idx_ptr = &idx;
    /* flag */
    int _contain_more_codes = 0;
    /* addressing flags */
    int address = 0;
    /* init of bin code */
    char* word = NULL;
    int n_operators = 0;
    sturct bucket* temp_data;
    /*
     * address -> A/R/E ->*/
    if ((word = get_word(line, idx_ptr))) {
        if (is_symbol(word))
            word = get_word(line, idx_ptr);
        word = get_word(line, idx_ptr);
        if ((word = get_word(line, idx_ptr)))
            if (inst->args-- >= 1) {
                n_operators++;
                if (is_ended_with_x(word, COMMA)) {
                    if (inst->args-- >= 1) {
                        found_comma = 1;
                        remove_last_char(word);
                    } else
                        ;
                    /* raise error illegal comma */
                } else {
                    if (is_register(word)) {
                        int temp = strlen(word);
                        temp = word[temp - 1] - '0';
                        code = add_bits(code, 3, n_operators * 2);
                        /* new code is temp
                         * if dest operand << 2
                         * if source operand << 5
                         * */
                    }
                    if (is_starting_with_x(word, HASH)) {
                        word++;
                        int temp = 0;
                        if ((temp_data = get_data_by_key(
                               assembler->symbol_table, word))) {
                            if (temp_data->data == MDEFINE) {
                                temp = atoi(temp_data->key);
                                /* code is unchanged, new code is temp << 2
                                 * address = 0; */
                            } else
                                ;
                            /* raise error : data has not been defined */
                        }
                        if (!temp)
                            if ((temp = atoi(word)))
                                ;
                            /* code is unchanged, new code is temp << 2
                             * address = 0; */
                            else
                                ;
                        /* raise value error */
                    }
                }
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
    struct instruction* inst = NULL;
    init_instruction(inst);
    FILE* obj_file = fopen(assembler->as_files->object_path, "w");

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
                    /* maybe i dont need to create bucket for every error
                     * or should i create tree of error ?! */
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
