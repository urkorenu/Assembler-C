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
    struct line_data* inst = NULL;
    FILE* ob_file = fopen(assembler->as_files->object_path, "w");

    assembler->ic = 100;

    while (get_line(line, source_file) != NULL) {
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
                    /* error - invalid syntax")*/;
                }

            } else {
                print_in_error(ERROR_CODE_28);
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
                } else {
                    /* error - "symbol is already initialized")*/;
                }
            }
        }
        if (is_e_instruction(word)) {
            if (strcmp(word, ".extern") == 0) {
                key = get_word(line, idx_ptr);
                insert_node(
                  assembler->symbol_table, key, create_bucket(NULL, EXTERNAL));
            }
        } else {
            if (reading_symbol) {
                if (!get_data_by_key(assembler->symbol_table, symbol)) {
                    struct bucket* b = create_bucket(CODE, NULL);
                    set_bucket_ic(b, assembler->ic);
                    insert_node(assembler->symbol_table, symbol, b);
                } else {
                    ;
                    /* error - symbol already initialized */
                }
            }
            if (get_instruction(inst, word)) {
                parse_line(assembler, line, inst);
                line_to_bin_1st(assembler, line, inst);
            }
            /* process commands */
        }
        word = NULL;
        symbol = NULL;
        idx = 0;
        memset(line, 0, MAXWORD);
        reading_symbol = 0;
        inst = NULL;
    }
    printf("printing object list into file....\n");
    print_linked_list(assembler->object_list, ob_file);
    printf("%s", "\nSymbol Table:\n");
    treeprint(assembler->symbol_table->root);
    return 1;
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
