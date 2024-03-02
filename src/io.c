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

char *modify_path(char *path)
{
    char *new_path = NULL;
    char footer[] = "_processed";
    int i;
    char *last_four = &path[strlen(path)-4];
    
    for (i=0; path[i] != '.'; i++)
        new_path[i] = path[i];

    strncat(new_path, footer, strlen(footer));
    strncat(new_path, last_four, 4);
    return new_path;

}


