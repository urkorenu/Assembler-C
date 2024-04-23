/*
 * File: utils.c
 * Description: This file contains utility functions for parsing and processing
 * strings.
 */

#include "io.h"
#include "error.h"
#include "instruction.h"
#include "parser.h"
#include <string.h>

FILE*
verbose_fopen(const char* fp, const char* modes)
{
    FILE* f;

    if (!fp)
        return NULL;
    if (!modes)
        modes = "r";

    f = fopen(fp, modes);

    if (!f)
        print_file_error(fp);

    return f;
}

/* Function to read a line from a file */
char*
get_line(char* line, FILE* file)
{
    char* result = fgets(line, MAXWORD, file);

    if (result == NULL && ferror(file)) {
        perror("Error reading from file:");
        clearerr(file);
    }
    return result;
}

/* Function to extract a word from a line */
void
get_word(const char* line, int* idx, char* word)
{
    int i = 0, j = idx[0];
    if (line == NULL || idx == NULL || word == NULL) {
        return;
    }

    while (isspace(line[j]))
        j++;

    while (line[j] != '\0' && line[j] != '=' && isgraph(line[j])) {
        if (line[j] == COMMA) {
            word[i++] = line[j++];
            break;
        }
        word[i++] = line[j++];
    }
    if (line[j] == '=' && i == 0)
        word[i++] = line[j++];

    word[i] = '\0';
    idx[0] = j;
}

int
get_string(char* line, char** start)
{
    char* tmp;

    if (!line || !line[0])
        return -1;

    line = strchr(line, '\"');

    if (line == NULL)
        return -1;

    tmp = line;
    line = strchr(line + 1, '\"');

    if (line != NULL) {
        start[0] = tmp;
        return line - start[0];
    }

    return -1;
}

/* Function to remove the last character from a string */
void
remove_last_char(char* word)
{
    int size = strlen(word);
    if (size > 0) {
        word[size - 1] = '\0';
    }
}

/* Function to remove the first character from a string */
void
remove_first_char(char* word)
{
    if (word[0] != '\0') {
        memmove(word, word + 1, strlen(word));
    }
}

/* Function to check if a word is a data store instruction */
int
is_data_store_instruction(const char* word)
{
    if (strcmp(word, ".data") == 0 || strcmp(word, ".string") == 0)
        return 1;
    return 0;
}

/* Function to check if a word is a symbol */
int
is_symbol(const char* word)
{
    int length = strlen(word);
    if (word[length - 1] == ':')
        return 1;
    return 0;
}

/* Function to check if a word ends with a specific character */
int
is_ends_with_x(const char* word, const char x)
{
    int length = strlen(word);
    if (length > 0 && word[length - 1] == x) {
        return 1;
    }
    return 0;
}

/* Function to check if a word starts with a specific character */
int
is_starting_with_x(const char* word, const char x)
{
    if (word[0] == x) {
        return 1;
    }
    return 0;
}

/* Function to check if a word is an E instruction */
int
is_e_instruction(const char* word)
{
    if (strcmp(word, ".extern") == 0 || strcmp(word, ".entry") == 0)
        return 1;
    return 0;
}

/* Function to check if a word is a register */
int
is_register(const char* word, int line_count)
{
    int len = strlen(word);
    if (len == 2 && word[0] == 'r' && isdigit(word[len - 1])) {
        int temp = word[len - 1] - '0';
        if (0 <= temp && temp <= 7)
            return 1;
        else {
            print_in_error(ILLEGAL_REG, line_count, word);
        }
    }
    return 0;
}

/* Function to duplicate a string */
char*
mystrdup(const char* s)
{
    char* p = (char*)malloc(strlen(s) + 1);
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed for string duplication\n");
        exit(EXIT_FAILURE);
    }

    strcpy(p, s);
    return p;
}

void*
int_to_voidp(int data)
{
    int* iptr = malloc(sizeof(int));
    if (iptr != NULL) {
        *iptr = data;
    }
    return iptr;
}

char*
remove_square_brackets(char* word)
{
    int len = strlen(word);
    int j = 0;
    int i;
    int found_brackets = 0;

    for (i = 0; i < len; i++) {
        if (word[i] != '[' && found_brackets == 0) {
            word[j++] = word[i];
        } else {
            word[i] = '\0';
            found_brackets = 1;
        }
    }

    word[j] = '\0';
    return word;
}

void
clean_word(char* word)
{
    if (is_ends_with_x(word, COMMA))
        remove_last_char(word);
    if (is_ends_with_x(word, ']'))
        word = remove_square_brackets(word);
}

int
is_comment(char* line)
{
    if (line[0] == ';')
        return 1;
    return 0;
}

int
is_legal_symbol(char* symbol, int line_count)
{
    struct line_data* inst = NULL;

    if (!symbol[0])
        return 1;
    inst = init_instruction(inst);

    if (get_instruction(inst, symbol) ||
        !strcmp(symbol, START_OF_MACRO_DEFINITION) ||
        !strcmp(symbol, END_OF_MACRO_DEFINITION) ||
        !strcmp(symbol, START_DATA_DEFINITION) ||
        !strcmp(symbol, START_STRING_DEFINITION) ||
        !strcmp(symbol, START_ENTRY_DEFINITION) ||
        !strcmp(symbol, START_EXTERN_DEFINITION)) {

        print_in_error(ILLEGAL_SYMBOL_NAME, line_count, symbol);
        free(inst);
        return 0;
    }
    free(inst);
    return 1;
}
