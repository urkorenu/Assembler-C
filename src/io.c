/*
 * File: utils.c
 * Description: This file contains utility functions for parsing and processing
 * strings.
 */

#include "io.h"
#include "parser.h"
#include <stdio.h>


FILE*
verbose_fopen(const char *fp, const char *modes)
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
    return fgets(line, MAXWORD, file);
}

/* Function to extract a word from a line */
char*
get_word(const char* line, int* idx)
{
    char* p;
    int i = 0;
    if (line == NULL || idx == NULL) {
        return NULL;
    }

    p = malloc(sizeof(char) * MAXWORD);
    if (p == NULL) {
        return NULL;
    }

    while (isspace(line[*idx]))
        (*idx)++;

    while ((line[*idx] != '\0' && isgraph(line[*idx])) || line[*idx] == '\"') {
        p[i++] = line[(*idx)++];
    }

    p[i] = '\0';

    return p;
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
is_ended_with_x(const char* word, const char x)
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
is_register(const char* word)
{
    int len = strlen(word);
    if (len == 2 && word[0] == 'r' && isdigit(word[len - 1])) {
        int temp = word[len - 1] - '0';
        if (0 <= temp && temp <= 7)
            return 1;
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
    int* iptr;
    iptr = malloc(sizeof(int));
    iptr[0] = data;
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
    if (is_ended_with_x(word, COMMA))
        remove_last_char(word);
    if (is_ended_with_x(word, ']'))
        word = remove_square_brackets(word);
}
