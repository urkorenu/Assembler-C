#include "assembler.h"
#include "Errors.h"
#include "binary_tree.h"
#include "bucket.h"
#include "encode.h"
#include "files.h"
#include "instruction.h"
#include "io.h"
#include "linked_list.h"
#include "parser.h"
#include <stdio.h>

const char ASSEMBLER_MEM_ERR[] = {
    "FATAL ERROR: Failed to allocate memory for struct assembler_data\n"
};

int
parse_first_phase(struct assembler_data* assembler, FILE* source_file)
{
    char line[MAXWORD];
    char* key = NULL;
    int idx = 0;
    int* idx_ptr = &idx;
    char* word = NULL;
    char* symbol = NULL;
    int reading_symbol = 0;
    int reading_data = 0;
    int is_valid = 1;
    int line_counter = 0;
    struct line_data* inst = NULL;
    while (get_line(line, source_file) != NULL) {
        line_counter++;
        inst = init_instruction(inst);
        word = get_word(line, idx_ptr);

        if (strcmp(word, ".define") == 0) {
            key = get_word(line, idx_ptr);
            if (!get_data_by_key(assembler->symbol_table, key)) {
                word = get_word(line, idx_ptr);
                if (strcmp(word, "=") == 0) {
                    word = get_word(line, idx_ptr);
                    /* maybe need conversion to int or else */
                    insert_node(assembler->symbol_table,
                                key,
                                create_bucket(word, to_void_ptr(MDEFINE)));
                } else {
                    is_valid = 0;
                    printf("err 1");
                    /* error - invalid syntax")*/;
                }

            } else {
                is_valid = 0;
                print_in_error(ERROR_CODE_28);
                printf("err 2");
            }
        } else if (is_symbol(word)) {
            int i = 0;
            int* temp_ptr = &i;
            symbol = get_word(word, temp_ptr);
            word = get_word(line, idx_ptr);
            reading_symbol = 1;
        }

        if (is_data_store_instruction(word)) {
            if (reading_symbol) {
                if (!get_data_by_key(assembler->symbol_table, symbol)) {
                    int* iptr;
                    struct bucket* b = create_bucket(CODE, NULL);
                    iptr = malloc(sizeof(int));
                    iptr[0] = assembler->ic;
                    b->data = iptr;
                    remove_last_char(symbol);
                    insert_node(assembler->symbol_table, symbol, b);
                    word = get_word(line, idx_ptr);
                    if (!word)
                        word = get_word(line, idx_ptr);
                    if (is_starting_with_x(word, '\"') &&
                        is_ended_with_x(word, '\"')) {
                        encode_string(assembler, line);
                    } else {
                        encode_data(assembler, line);
                    }
                    reading_data = 1;
                } else {
                    is_valid = 0;
                    printf("err 3");
                    /* error - "symbol is already initialized")*/;
                }
            }
        }
        if (is_e_instruction(word)) {
            if (strcmp(word, ".extern") == 0) {
                key = get_word(line, idx_ptr);
                insert_node(
                  assembler->symbol_table, key, create_bucket(EXTERNAL, NULL));
            }
        } else {
            if (reading_symbol && !reading_data) {
                if (!get_data_by_key(assembler->symbol_table, symbol)) {
                    struct bucket* b = create_bucket(CODE, NULL);
                    set_bucket_ic(b, assembler->ic);
                    remove_last_char(symbol);
                    insert_node(assembler->symbol_table, symbol, b);
                } else {
                    is_valid = 0;
                    printf("err 4\n");
                    printf("At line: %d\n", line_counter);
                    printf("%s", line);
                    /* error - symbol already initialized */
                }
            }
            if (get_instruction(inst, word)) {
                parse_line(assembler, line, inst);
                line_to_bin_1st(assembler, line, inst);
            }
        }
        word = NULL;
        symbol = NULL;
        idx = 0;
        memset(line, 0, MAXWORD);
        reading_symbol = 0;
        reading_data = 0;
        inst = NULL;
    }
    /* tests : */
    printf("%s", "\nSymbol Table:\n");
    treeprint(assembler->symbol_table->root);
    return is_valid;
}

int
parse_second_phase(struct assembler_data* assembler, FILE* source_file)
{
    char line[MAXWORD];
    int idx = 0;
    int* idx_ptr = &idx;
    char* word = NULL;
    int code = 0;
    int ic;
    int line_counter = 0;
    int node_ic = 100;
    int* node_ptr = &node_ic;
    struct bucket* data;
    int entry_flag, extern_flag = 0;
    struct line_data* inst = NULL;
    struct linked_list* entry_list = create_new_ll_node(0);
    struct linked_list* extern_list = create_new_ll_node(0);
    struct linked_list* last_unset_node;
    FILE *en_file, *ex_file;
    int is_valid = 1;
    assembler->ic = 100;
    last_unset_node = get_last_unset_node(assembler->object_list, node_ptr);
    fseek(source_file, 0, SEEK_SET);
    while (get_line(line, source_file) != NULL) {
        line_counter++;
        code = 0;
        inst = init_instruction(inst);
        word = get_word(line, idx_ptr);
        if (is_symbol(word)) {
            word = get_word(line, idx_ptr);
        }
        if ((is_data_store_instruction(word)) ||
            ((strcmp(word, ".extern") == 0))) {
            continue;
        } else if ((strcmp(word, ".entry") == 0)) {
            word = get_word(line, idx_ptr);
            if ((data = (get_data_by_key(assembler->symbol_table, word)))) {
                ic = ((int*)data->data)[0];
                insert_ll_node(entry_list,
                               create_bucket(word, int_to_voidp(ic)));
                entry_flag = 1;
            } else {
                /* if the symbol not exist it the table */
                print_in_error(ERROR_CODE_29);
                is_valid = 0;
                printf("line : %d\n", line_counter);
            }
        } else {
            while (word[0] != NULL) {
                if (is_ended_with_x(word, COMMA))
                        remove_last_char(word);
                /* remove index from word */
                if (is_ended_with_x(word, ']'))
                    word = remove_square_brackets(word);
                /* if the symbol is not found in the table */
                data = get_data_by_key(assembler->symbol_table, word);
                if (!data) {
                    word = get_word(line, idx_ptr);
                    continue;
                } else if (data->data != NULL && (strcmp(data->key, CODE) == 0)) {
                    code = add_bits(int_to_voidp(code), 2, 0);
                    code = add_bits(int_to_voidp(code), ((int*)data->data)[0], 2);
                    set_data_int(last_unset_node, code);

                    last_unset_node =
                      get_last_unset_node(last_unset_node, node_ptr);
                }

                else if (data->data == NULL) {
                    code = add_bits(int_to_voidp(code), 1, 0);
                    set_data_int(last_unset_node, code);
                    insert_ll_node(extern_list,
                                   create_bucket(word, int_to_voidp(node_ic-1)));
                    extern_flag = 1;
                    last_unset_node =
                      get_last_unset_node(last_unset_node, node_ptr);
                }

                word = get_word(line, idx_ptr);
            }
        }
        word = NULL;
        idx = 0;
        memset(line, 0, MAXWORD);
        inst = NULL;
    }
    if (entry_flag == 1) {
        en_file = fopen(assembler->as_files->entries_path, "w");
        print_e_list(entry_list, en_file, "\n");
    }
    if (extern_flag == 1) {
        ex_file = fopen(assembler->as_files->externals_path, "w");
        print_e_list(extern_list, ex_file, "\n");
    }
    return is_valid;
}
struct assembler_data*
assembler_alloc(void)
{
    struct assembler_data* assembler = malloc(sizeof(struct assembler_data));

    if (assembler == NULL) {
        fprintf(stderr, ASSEMBLER_MEM_ERR);
        return NULL;
    }
    return assembler;
}
void
assembler_free(struct assembler_data* assembler)
{
    if (assembler == NULL)
        return;

    assembler_reset(assembler);
    free(assembler);
    assembler = NULL;
}

struct assembler_data
assembler_init(void)
{
    struct assembler_data assembler;

    assembler.errors = create_new_ll_node(0);
    assembler.object_list = create_new_ll_node(0);
    assembler.symbol_table = create_new_btree();
    assembler.macro_tree = create_new_btree();
    assembler.as_files = files_alloc();
    assembler.ic = 100;
    assembler.instruction_c = 0;
    assembler.data_c = 0;
    return assembler;
}

void
assembler_reset(struct assembler_data* assembler)
{
    llfree(assembler->errors);
    llfree(assembler->object_list);
    btree_free(assembler->symbol_table);
    btree_free(assembler->macro_tree);
    files_free(assembler->as_files);
    memset(assembler, 0, sizeof(struct assembler_data));
}
