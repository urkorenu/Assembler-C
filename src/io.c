#include "io.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char*
get_line(char* line, FILE* file)
{
    return fgets(line, MAXWORD, file);
}

char*
get_word(char* line, int* idx)
{
    if (line == NULL || idx == NULL) {
        return NULL;
    }

    char* p = malloc(sizeof(char) * MAX_LEN);
    if (p == NULL) {
        return NULL;
    }

    int i = 0;

    while (line[*idx] == ' ' || line[*idx] == '\t')
        (*idx)++;

    while ((line[*idx] != '\0' && isgraph(line[*idx])) || line[*idx] == '\"') {
        p[i++] = line[(*idx)++];
    }

    p[i] = '\0';

    return p;
}

void
remove_last_char(char* word)
{
    int size = strlen(word);
    word[size - 1] = '\0';
    return;
}

void
remove_first_char(char* word)
{
    word++;
    return;
}

int
is_data_store_instruction(char* word)
{
    if (strcmp(word, ".data") == 0)
        return 1;
    else if (strcmp(word, ".string") == 0)
        return 1;
    return 0;
}

int
is_symbol(char* word)
{
    int length = strlen(word);
    if (word[length - 1] == ':')
        return 1;
    return 0;
}

int
is_ended_with_x(char* word, char x)
{
    int length = strlen(word);
    if (word[length - 1] == x)
        return 1;
    return 0;
}

int
is_starting_with_x(char* word, char x)
{
    if (word[0] == x)
        return 1;
    return 0;
}

int
is_e_instruction(char* word)
{
    if (strcmp(word, ".extern") == 0)
        return 1;
    else if (strcmp(word, ".entry") == 0)
        return 1;
    return 0;
}

int
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
