#include "binary_tree.h"
#include "includes.h"
#include "io.h"
#include "macro.h"
#include <string.h>

/* void parser(FILE *file, void *host, int mode) 
{
    switch (mode) {
        case 1:
            parse_pre_proccesor(file, host);
        case 2:
            parse_x(file, host);
    }
} */

void parse_pre_proccesor(FILE *file, void *host, FILE *new_file)
{
   int line_count = 1;
   char line[MAXWORD];
   char *key = NULL;
   int idx = 0;
   int *idx_ptr = &idx;
   char *word = NULL;
   int reading_macro = 0;
   int start_idx;


   while (get_line(line, file) != NULL) {
       while ((word = get_word(line, idx_ptr))) {
           if (!reading_macro) {
               if (strcmp(word, "mcr") == 0) {
                   reading_macro = 1;
                   key = get_word(line, idx_ptr);
                   start_idx = line_count++;
                   break;
                }
               else {
                   fprintf(new_file, "%s", line);
                   ++line_count;
                   break;
               }
           }
           
           else {
               if (strcmp(word, "endmcr") == 0) {
                   struct macro *macro = NULL;
                   macro = create_macro(&macro ,start_idx, (++line_count));
                   insert_node(host, key, macro);
                   reading_macro = 0;
                   break;
               }
               else { break;}
           }
       }
       word = NULL;
       idx = 0;
       memset(line, 0, MAXWORD);
   }
}



