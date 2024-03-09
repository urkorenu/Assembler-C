#include "io.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char *get_line(char *line, FILE *file) 
{
    return fgets(line, MAXWORD, file);
}

char *get_word(char *line, int *idx)
{
    if (line == NULL || idx == NULL) {
        return NULL;
    }

    char *p = malloc(sizeof(char) * 100);
    if (p == NULL) {
        return NULL; 
    }

    int i = 0;

    while (line[*idx] == ' ' || line[*idx] == '\t')
        (*idx)++;

    while (line[*idx] != '\0' && isgraph(line[*idx])) {
        p[i++] = line[(*idx)++];
    }

    p[i] = '\0'; 

    return p;
}





