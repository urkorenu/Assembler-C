#include "include/parser.h"
#include "include/assembler.h"
#include "include/bucket.h"
#include "include/error.h"
#include "include/io.h"
#include "include/linked_list.h"

static void
process_regular_line(FILE* read_file,
                     FILE* write_file,
                     char* line,
                     int* line_count,
                     struct assembler_data* assembler,
                     int* reading_macro,
                     int* start_idx,
                     fpos_t* temp_pos,
                     char** key)
{
    int idx = 0;
    char word[MAXWORD];
    struct macro* temp = NULL;

    get_word(line, &idx, word);
    if (strcmp(word, "mcr") == 0) {
        (*reading_macro) = 1;
        get_word(line, &idx, key[0]);
        (*start_idx) = ++(*line_count);
        fgetpos(read_file, temp_pos);
    } else {
        temp = get_data_by_key(assembler->macro_tree, word);
        if (temp) {
            fgetpos(read_file, temp_pos);
            insert_macro(temp, read_file, write_file);
            fsetpos(read_file, temp_pos);
            ++(*line_count);
        } else {
            fprintf(write_file, "%s", line);
            ++(*line_count);
        }
    }
}

static void
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
    int idx = 0;
    char word[MAXWORD];

    get_word(line, &idx, word);

    if (strcmp(word, "endmcr") == 0) {
        struct macro* macro =
          create_macro(&macro, temp_pos, *line_count - start_idx);
        insert_node(assembler->macro_tree, key, macro);
        (*reading_macro) = 0;
    } else {
        (*line_count)++;
    }
}

void
parse_pre_processor(struct assembler_data* assembler)
{
    int start_idx;
    fpos_t temp_pos;
    char* key = NULL;
    int line_count = 1;
    int reading_macro = 0;
    FILE* read_file = NULL;
    FILE* write_file = NULL;
    char line[MAXWORD] = { 0 };

    if (!try_init_files((*assembler->as_files), &read_file, &write_file))
        return;

    while (get_line(line, read_file) != NULL) {
        if (!line[0])
            continue;
        if (is_comment(line))
            continue;
        if (!reading_macro) {
            process_regular_line(read_file,
                                 write_file,
                                 line,
                                 &line_count,
                                 assembler,
                                 &reading_macro,
                                 &start_idx,
                                 &temp_pos,
                                 &key);

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
    fclose(read_file);
    fclose(write_file);
}

char*
get_index(char* word)
{
    int i, j = 0;
    int len = strlen(word);
    int inside_square_brackets = 0;
    char* index = malloc(sizeof(char) * MAXWORD);
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
parse_line(struct assembler_data* assembler,
           char* line,
           struct line_data* inst,
           int line_count)
{
    int idx = 0;
    char word[MAXWORD];
    int found_comma = 0;

    get_word(line, &idx, word);

    while (word[0]) {
        if (is_symbol(word)) {
            get_word(line, &idx, word);
        }
        if (get_instruction(inst, word)) {
            if (inst->args == 2) {
                get_word(line, &idx, word);
                if (is_ends_with_x(word, COMMA)) {
                    found_comma = 1;
                    remove_last_char(word);
                    inst->source = str_dup(word);
                } else {
                    inst->source = str_dup(word);
                }
                if (!found_comma) {
                    get_word(line, &idx, word);
                    if (is_starting_with_x(word, COMMA)) {
                        remove_first_char(word);
                    } else {
                        inst->is_valid = 0;
                        print_in_error(MISSING_COMMA, line_count, NULL);
                        return 0;
                    }
                }
            }
            if (inst->args >= 1) {
                get_word(line, &idx, word);
                if (!word[0]) {
                    inst->is_valid = 0;
                    print_in_error(MISSING_ARG, line_count, NULL);
                    return 0;
                }
                if (is_ends_with_x(word, COMMA)) {
                    inst->is_valid = 0;
                    print_in_error(EXTRA_COMMAS, line_count, NULL);
                    return 0;
                }
                inst->destination = str_dup(word);
            }
            get_word(line, &idx, word);
            if (word[0]) {
                inst->is_valid = 0;
                print_in_error(EXTRA_TEXT, line_count, NULL);
                return 0;
            }

        } else {
            inst->is_valid = 0;
            print_in_error(INVALID_COMMAND, line_count, word);
            return 0;
        }
    }
    return 1;
}

int
line_to_bin(struct assembler_data* assembler,
            char* line,
            struct line_data* inst,
            int line_count)
{
    int found_reg = 0;
    char* index = NULL;
    int opcode = inst->code << 6;
    struct linked_list* source_code =
      insert_ll_node(assembler->object_list, int_to_voidp(opcode));
    assembler->instruction_c++;
    assembler->ic++;

    if (inst->source) {
        encode_operand(assembler,
                       inst,
                       source_code,
                       inst->source,
                       1,
                       &found_reg,
                       line_count);
        free(inst->source);
    }
    if (inst->destination) {
        encode_operand(assembler,
                       inst,
                       source_code,
                       inst->destination,
                       0,
                       &found_reg,
                       line_count);
        free(inst->destination);
    }

    free(index);
    return 0;
}

int
parse_define(struct assembler_data* assembler,
             char* line,
             int* idx,
             int line_count)
{
    char key[MAXWORD];
    char word[MAXWORD];

    get_word(line, idx, key);

    if (!is_legal_symbol(key, line_count))
        return 0;
    if (!key[0]) {
        print_in_error(MISSING_ARG, line_count, NULL);
        return 0;
    }

    if (get_data_by_key(assembler->symbol_table, key)) {
        print_in_error(SYMBOL_DEFINED, line_count, key);
        return 0;
    }

    get_word(line, idx, word);
    if (!word[0] || strcmp(word, "=") != 0) {
        print_in_error(ILLEGAL_ARG, line_count, word);
        return 0;
    }

    get_word(line, idx, word);
    if (!word[0]) {
        print_in_error(MISSING_ARG, line_count, NULL);
        return 0;
    }

    insert_node(
      assembler->symbol_table, key, create_bucket(word, to_void_ptr(MDEFINE)));
    return 1;
}

static int
handle_symbol(struct assembler_data* assembler,
              char* symbol,
              int* idx,
              int line_count)
{
    struct bucket* b = create_bucket(CODE, NULL);
    remove_last_char(symbol);

    if (symbol == NULL) {
        print_in_error(MISSING_ARG, line_count, NULL);
        return 0;
    }
    if (get_data_by_key(assembler->symbol_table, symbol)) {
        print_in_error(SYMBOL_DEFINED, line_count, symbol);
        return 0;
    }
    if (!is_legal_symbol(symbol, line_count))
        return 0;

    set_bucket_ic(b, assembler->ic);
    insert_node(assembler->symbol_table, symbol, b);
    return 1;
}

static void
process_data(struct assembler_data* assembler,
             char* line,
             int* reading_data,
             int* idx,
             int line_count)
{
    char word[MAXWORD];

    get_word(line, idx, word);

    if (!word[0])
        get_word(line, idx, word);

    if (is_starting_with_x(word, '\"')) {
        encode_string(assembler, line, line_count);
    } else {
        encode_data(assembler, line, line_count);
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
                             int* idx,
                             int line_count)
{
    if ((*reading_symbol)) {
        if (!handle_symbol(assembler, symbol, idx, line_count))
            return 0;
        process_data(assembler, line, reading_data, idx, line_count);
    }
    return 1;
}

int
parse_extern(struct assembler_data* assembler,
             char* line,
             int* idx,
             int line_count)
{
    char key[MAXWORD];

    get_word(line, idx, key);

    if (!key[0]) {
        print_in_error(MISSING_ARG, line_count, NULL);
        return 0;
    }

    insert_node(assembler->symbol_table, key, create_bucket(EXTERNAL, NULL));
    return 1;
}

int
parse_instruction(struct assembler_data* assembler,
                  char* line,
                  int* idx,
                  int reading_data,
                  int reading_symbol,
                  char* symbol,
                  int* line_counter,
                  char* word,
                  int line_count)
{
    struct line_data* inst = NULL;

    if (reading_symbol && !reading_data) {
        if (handle_symbol(assembler, symbol, idx, line_count))
            if (!word[0]) {
                print_in_error(MISSING_ARG, line_count, NULL);
                return 0;
            }
    }

    inst = init_instruction(inst);
    if (get_instruction(inst, word)) {
        parse_line(assembler, line, inst, line_count);
        line_to_bin(assembler, line, inst, line_count);
    }

    free(inst);
    return 1;
}

static int
process_entry(struct assembler_data* assembler,
              char* line,
              int* line_counter,
              struct linked_list* entry_list,
              int* entry_flag,
              int* idx,
              char* word,
              int line_count)
{

    int ic;
    struct bucket* data;

    get_word(line, idx, word);

    if (!(data = (get_data_by_key(assembler->symbol_table, word)))) {
        print_in_error(SYMBOL_NOT_FOUND, line_count, word);
        return 0;
    }
    if (strcmp(data->key, EXTERNAL) == 0) {
        print_in_error(ENTRY_IS_EXTERNAL, line_count, word);
        return 0;
    }
    ic = ((int*)data->data)[0];
    insert_ll_node(entry_list, create_bucket(word, int_to_voidp(ic)));
    (*entry_flag) = 1;
    return 1;
}

static void
process_words(struct assembler_data* assembler,
              char* word,
              char* line,
              int* idx,
              struct linked_list* extern_list,
              int* extern_flag,
              int* node_ic,
              struct linked_list* last_unset_node)
{
    int ic;
    int code = 0;
    int* tmp_p = NULL;
    struct bucket* data;

    while (word[0]) {
        clean_word(word);
        data = get_data_by_key(assembler->symbol_table, word);
        if (!data) {
            /* not in symbol table */
            get_word(line, idx, word);
            continue;
        } else if (data->data != NULL && (strcmp(data->key, CODE) == 0)) {
            /* in symbol table and its code */
            tmp_p = int_to_voidp(2);
            code = add_bits(tmp_p, ((int*)data->data)[0], 2);
            set_data_int(last_unset_node, code);
            last_unset_node =
              get_first_unset_node(assembler->object_list, node_ic);
        } else if (data->data == NULL) {
            /* in symbol table but its null (extern) */
            tmp_p = int_to_voidp(code);
            code = add_bits(tmp_p, 1, 0);
            set_data_int(last_unset_node, code);
            ic = (*node_ic);
            insert_ll_node(extern_list,
                           create_bucket(word, int_to_voidp(ic - 1)));
            (*extern_flag) = 1;
            last_unset_node =
              get_first_unset_node(assembler->object_list, node_ic);
        }
        if (tmp_p)
            free(tmp_p);
        get_word(line, idx, word);
    }
}

int
process_line(struct assembler_data* assembler,
             char* line,
             int* line_counter,
             struct linked_list* entry_list,
             int* entry_flag,
             struct linked_list* extern_list,
             int* extern_flag,
             struct linked_list* last_unset_node,
             int* node_ic)
{
    int idx = 0;
    int is_valid = 1;
    char word[MAXWORD];

    get_word(line, &idx, word);

    if (is_symbol(word)) {
        get_word(line, &idx, word);
    }
    if ((is_data_store_instruction(word)) || ((strcmp(word, ".extern") == 0))) {
        return is_valid;
    } else if ((strcmp(word, ".entry") == 0)) {
        is_valid = process_entry(assembler,
                                 line,
                                 line_counter,
                                 entry_list,
                                 entry_flag,
                                 &idx,
                                 word,
                                 (*line_counter));
    } else {
        process_words(assembler,
                      word,
                      line,
                      &idx,
                      extern_list,
                      extern_flag,
                      node_ic,
                      last_unset_node);
    }
    return is_valid;
}
