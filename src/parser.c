#include "parser.h"
#include "assembler.h"
#include "io.h"

void
process_regular_line(FILE* read_file,
                     FILE* write_file,
                     char* line,
                     int* line_count,
                     struct assembler_data* assembler,
                     int* reading_macro,
                     int* start_idx,
                     fpos_t temp_pos,
                     char* key);
void
process_macro_line(FILE* read_file,
                   FILE* write_file,
                   char* line,
                   int* line_count,
                   struct assembler_data* assembler,
                   char* key,
                   int start_idx,
                   fpos_t temp_pos,
                   int* reading_macro);

/**
 * @brief Parses the read_file and operate the pre-processor into a read_file.
 *
 * This function reads pre-processor directives from the given read_file and
 * performs appropriate actions based on the directives encountered.
 *
 * @param read_file      Pointer to the input read_file.
 * @param assembler->macro_tree      Pointer to the assembler->macro_tree data
 * structure.
 * @param write_file  Pointer to the output read_file.
 */
void
parse_pre_processor(struct assembler_data* assembler)
{
    FILE *read_file, *write_file;
    int line_count = 1;
    char line[MAXWORD];
    char* key = NULL;
    int start_idx;
    int reading_macro = 0;
    fpos_t temp_pos = 0;

    read_file = fopen(assembler->as_files->assembly_path, "r");
    if (read_file == NULL) {
        fprintf(stderr,
                "Error opening read_file %s: ",
                assembler->as_files->assembly_path);
        perror("");
        return;
    }
    write_file = fopen(assembler->as_files->processed_path, "w");

    while (get_line(line, read_file) != NULL) {
        if (!reading_macro) {
            process_regular_line(read_file,
                                 write_file,
                                 line,
                                 &line_count,
                                 assembler,
                                 &reading_macro,
                                 &start_idx,
                                 temp_pos,
                                 key);

        }

        else {
            process_macro_line(read_file,
                               write_file,
                               line,
                               &line_count,
                               assembler,
                               key,
                               start_idx,
                               temp_pos,
                               &reading_macro);
        }
    }
    memset(line, 0, MAXWORD);

    fclose(read_file);
    fclose(write_file);
}

void
process_regular_line(FILE* read_file,
                     FILE* write_file,
                     char* line,
                     int* line_count,
                     struct assembler_data* assembler,
                     int* reading_macro,
                     int* start_idx,
                     fpos_t temp_pos,
                     char* key)
{
    char* word = NULL;
    int idx = 0;
    struct macro* temp = NULL;

    word = get_word(line, &idx);
    if (strcmp(word, "mcr") == 0) {
        (*reading_macro) = 1;
        key = get_word(line, &idx);
        (*start_idx) = ++(*line_count);
        fgetpos(read_file, &temp_pos);
    } else {
        temp = get_data_by_key(assembler->macro_tree, word);
        if (temp) {
            fgetpos(read_file, &temp_pos);
            insert_macro(temp, read_file, write_file);
            fsetpos(read_file, &temp_pos);
            ++(*line_count);
        } else {
            fprintf(write_file, "%s", line);
            ++(*line_count);
        }
    }
}

void
process_macro_line(FILE* read_file,
                   FILE* write_file,
                   char* line,
                   int* line_count,
                   struct assembler_data* assembler,
                   char* key,
                   int start_idx,
                   fpos_t temp_pos,
                   int* reading_macro)
{
    char* word = NULL;
    int idx = 0;

    word = get_word(line, &idx);

    if (strcmp(word, "endmcr") == 0) {
        struct macro* macro =
          create_macro(&macro, temp_pos, *line_count - start_idx);
        insert_node(assembler->macro_tree, key, macro);
        (*reading_macro) = 0;
    } else {
        (*line_count)++;
    }
}

char*
get_index(char* word)
{
    int i, j = 0;
    int len = strlen(word);
    int inside_square_brackets = 0;
    char* index = malloc(sizeof(char) * MAX_LEN);
    if (index == NULL) {
        return NULL;
    }
    for (i = 0; i <= len; i++) {
        if (word[i] == '[')
            inside_square_brackets = 1;
        else if (inside_square_brackets && word[i] == ']') {
            if (j) {
                index[j] = '\0';
                return index;
            }
        } else if (inside_square_brackets) {
            index[j++] = word[i];
            word[i] = '0';
        }
    }
    free(index);
    return NULL;
}

int
parse_line(struct assembler_data* assembler, char* line, struct line_data* inst)
{
    char* word = NULL;
    int idx = 0;
    int found_comma;
    word = get_word(line, &idx);
    while (word[0]) {
        if (is_symbol(word)) {
            inst->symbol = mystrdup(word);
            word = get_word(line, &idx);
        }
        if (get_instruction(inst, word)) {
            if (inst->args == 2) {
                word = get_word(line, &idx);
                if (is_ended_with_x(word, COMMA)) {
                    found_comma = 1;
                    remove_last_char(word);
                    inst->source = mystrdup(word);
                } else {
                    inst->source = mystrdup(word);
                }
                if (!found_comma) {
                    word = get_word(line, &idx);
                    if (is_starting_with_x(word, COMMA)) {
                        remove_first_char(word);
                        if (word[0] != '0')
                            idx -= (strlen(word)) - 1;
                    } else {
                        inst->is_valid = 0;
                        /* error : missing comma */
                        print_in_error(ERROR_CODE_29);
                        return 0;
                    }
                }
            }
            if (inst->args >= 1) {
                word = get_word(line, &idx);
                if (is_ended_with_x(word, COMMA)) {
                    inst->is_valid = 0;
                    /* error - too many commas */
                    print_in_error(ERROR_CODE_39);
                    return 0;
                }
                inst->destination = mystrdup(word);
            }
            word = get_word(line, &idx);
            if (word[0]) {
                inst->is_valid = 0;
                /* error  - too much text */
                print_in_error(ERROR_CODE_32);
                return 0;
            }

        } else {
            inst->is_valid = 0;
            /* error : not a valid command */
            print_in_error(ERROR_CODE_38);
            return 0;
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
      insert_ll_node(assembler->object_list, int_to_voidp(opcode));
    assembler->instruction_c++;
    assembler->ic++;
    if (inst->source) {
        encode_operand(
          assembler, inst, source_code, inst->source, 1, &found_reg);
    }
    if (inst->destination) {
        encode_operand(
          assembler, inst, source_code, inst->destination, 0, &found_reg);
    }

    free(index);
    return 0;
}

int
parse_define(struct assembler_data* assembler, char* line, int* idx)
{
    char* word = NULL;
    char* key = get_word(line, idx);
    if (key == NULL) {
        printf("Error: Invalid syntax for .define.\n");
        return 0;
    }

    if (get_data_by_key(assembler->symbol_table, key)) {
        print_in_error(ERROR_CODE_28);
        printf("Error: Symbol '%s' already defined.\n", key);
        return 0;
    }

    word = get_word(line, idx);
    if (word == NULL || strcmp(word, "=") != 0) {
        printf("Error: Invalid syntax for .define.\n");
        return 0;
    }

    word = get_word(line, idx);
    if (word == NULL) {
        printf("Error: Invalid syntax for .define.\n");
        return 0;
    }

    insert_node(
      assembler->symbol_table, key, create_bucket(word, to_void_ptr(MDEFINE)));
    return 1;
}

static int
handle_symbol(struct assembler_data* assembler, char* symbol, int* idx)
{
    int* iptr;
    struct bucket* b = create_bucket(CODE, NULL);

    if (get_data_by_key(assembler->symbol_table, symbol)) {
        /* error - "symbol is already initialized")*/;
        return 0;
    }

    iptr = malloc(sizeof(int));
    iptr[0] = assembler->ic;
    b->data = iptr;
    remove_last_char(symbol);
    insert_node(assembler->symbol_table, symbol, b);
    return 1;
}

static void
process_data(struct assembler_data* assembler,
             char* line,
             int* reading_data,
             int* idx)
{
    char* word = get_word(line, idx);
    if (!word)
        word = get_word(line, idx);
    if (is_starting_with_x(word, '\"') && is_ended_with_x(word, '\"')) {
        encode_string(assembler, line);
    } else {
        encode_data(assembler, line);
    }
    (*reading_data) = 1;
}

int
parse_data_store_instruction(struct assembler_data* assembler,
                             char* line,
                             char* word,
                             int* reading_symbol,
                             int* reading_data,
                             char* symbol,
                             int* idx)
{
    if ((*reading_symbol)) {
        if (!handle_symbol(assembler, symbol, idx))
            return 0;

        process_data(assembler, line, reading_data, idx);
    }
    return 1;
}

int
parse_extern(struct assembler_data* assembler, char* line, int* idx)
{
    char* key = get_word(line, idx);
    if (key == NULL) {
        printf("Error: Invalid syntax for .extern.\n");
        return 0;
    }

    insert_node(assembler->symbol_table, key, create_bucket(EXTERNAL, NULL));
    return 1;
}

int
parse_instruction(struct assembler_data* assembler,
                  char* line,
                  int* idx,
                  int* reading_data,
                  int* reading_symbol,
                  char* symbol,
                  int* line_counter,
                  char* word)
{
    struct line_data* inst = NULL;
    struct bucket* b = create_bucket(CODE, NULL);
    inst = init_instruction(inst);
    if ((*reading_symbol) && !(*reading_data)) {
        if (get_data_by_key(assembler->symbol_table, symbol)) {
            /* error - symbol already initialized */
            printf("At line: %d\n", (*line_counter));
            return 0;
        }
        set_bucket_ic(b, assembler->ic);
        remove_last_char(symbol);
        insert_node(assembler->symbol_table, symbol, b);
    }

    if (get_instruction(inst, word)) {
        parse_line(assembler, line, inst);
        line_to_bin_1st(assembler, line, inst);
    }

    inst = NULL;
    return 1;
}
