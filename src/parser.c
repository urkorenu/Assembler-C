#include "parser.h"
#include "Errors.h"
#include "binary_tree.h"
#include "bucket.h"
#include "encode.h"
#include "files.h"
#include "includes.h"
#include "instruction.h"
#include "io.h"
#include "linked_list.h"
#include "macro.h"

const char ASSEMBLER_MEM_ERR[] = {
    "FATAL ERROR: Failed to allocate memory for struct assembler_data\n"
};

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

/**
 * @brief Parses the file and operate the pre-processor into a file.
 *
 * This function reads pre-processor directives from the given file and performs
 * appropriate actions based on the directives encountered.
 *
 * @param file      Pointer to the input file.
 * @param host      Pointer to the host data structure.
 * @param new_file  Pointer to the output file.
 */
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

static char*
get_index(char* word)
{
    int i;
    int j = 0;
    int len = strlen(word);
    int inside_square_brackets = 0;
    char* p = malloc(sizeof(char) * MAX_LEN);
    if (p == NULL) {
        return NULL;
    }
    for (i = 0; i <= len; i++) {
        if (word[i] == '[')
            inside_square_brackets = 1;
        else if (inside_square_brackets) {
            if (word[i] == ']') {
                if (j) {
                    p[j] = '\0';
                    return p;
                }
            }
            p[j++] = word[i];
            word[i] = '0';
        }
    }
    return NULL;
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
            inst->symbol = (char*)malloc(strlen(word) + 1);
            inst->symbol = word;
            word = get_word(line, idx_ptr);
        }
        if (get_instruction(inst, word)) {
            if (inst->args == 2) {
                word = get_word(line, idx_ptr);
                if (is_ended_with_x(word, COMMA)) {
                    found_comma = 1;
                    remove_last_char(word);
                    inst->source = mystrdup(word);
                    /* inst->source = word; */
                } else {
                    inst->source = mystrdup(word);
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
                        print_in_error(ERROR_CODE_29);
                    }
                }
            }
            if (inst->args >= 1) {
                word = get_word(line, idx_ptr);
                if (is_ended_with_x(word, COMMA)) {
                    inst->is_valid = 0;
                    return 0;
                    /* error - too many commas */
                    print_in_error(ERROR_CODE_39);
                }
                inst->destination = mystrdup(word);
            }
            if ((word = get_word(line, idx_ptr))) {
                inst->is_valid = 0;
                return 0;
                /* error  - too much text */
                print_in_error(ERROR_CODE_32);
            }

        } else {
            inst->is_valid = 0;
            /* error : not a valid command */
            print_in_error(ERROR_CODE_38);
        }
    }
    return 1;
}

int
line_to_bin_1st(struct assembler_data* assembler,
                char* line,
                struct line_data* inst)
{
    int opcode = inst->code << 6;
    int found_reg = 0;
    char* index = NULL;
    struct linked_list* source_code =
      insert_ll_node(assembler->object_list, opcode);
    assembler->ic++;
    if (inst->source) {
        if (is_register(inst->source)) {
            encode_register(assembler, inst, found_reg, source_code, 1);
            found_reg = 1;
        } else if (is_starting_with_x(inst->source, HASH)) {
            encode_direct(assembler, inst, source_code, 1);
        } else if ((index = get_index(inst->source))) {
            encode_index(assembler, inst, source_code, 1, index);
        } else {
            encode_null(assembler, inst, source_code, 1);
        }
    }
    if (inst->destination) {
        if (is_register(inst->destination)) {
            encode_register(assembler, inst, found_reg, source_code, 0);
            found_reg = 1;
        } else if (is_starting_with_x(inst->destination, HASH)) {
            encode_direct(assembler, inst, source_code, 0);
        } else if ((index = get_index(inst->destination))) {
            encode_index(assembler, inst, source_code, 0, index);
        } else {

            encode_null(assembler, inst, source_code, 0);
        }
    }

    free(index);
    return 0;
}

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
                    insert_node(assembler->symbol_table,
                                symbol,
                                create_bucket(DATA, (void*)(&assembler->ic)));
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
                    int* iptr;
                    struct bucket *b = create_bucket(CODE, NULL);
                    iptr = malloc(sizeof(int));
                    iptr[0] = assembler->ic;
                    b->data = iptr;
                    /* maybe need conversion to int or else */
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
    print_linked_list(assembler->object_list, ob_file);
    printf("%s", "\nSymbol Table:\n");
    treeprint(assembler->symbol_table->root);
    return 1;
}
