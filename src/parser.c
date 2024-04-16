#include "parser.h"
#include "io.h"

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

char*
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
      insert_ll_node(assembler->object_list, int_to_voidp(opcode));
    assembler->instruction_c++;
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
