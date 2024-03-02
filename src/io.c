#include "io.h"
#include <stdio.h>
#include <string.h>


char *get_line(char *line, FILE *file) 
{
    return fgets(line, MAXWORD, file);
}

char *get_word(char *line ,char *delimiters)
{
    return strtok(line, delimiters);
}

char *modify_path(const char *path) {

    char *new_path = malloc(strlen(path) + 20); 
    if (new_path == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    char footer[] = "_processed";
    const char *last_four = &path[strlen(path)-4]; 

    int i;
    for (i = 0; path[i] != '.' && path[i] != '\0'; i++) {
        new_path[i] = path[i];
    }

    strcat(new_path, footer);
    strcat(new_path, last_four);

    return new_path;
}



