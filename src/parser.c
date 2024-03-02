#include "binary_tree.h"
#include "includes.h"
#include "io.h"
#include "macro.h"

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
   char *word = NULL;
   int reading_macro = 0;
   int start_idx, end_idx;


   while (get_line(line, file) != NULL) {
       while ((word = get_word(line, " ,;.\t\n")) != NULL) {
           if (!reading_macro) {
               if (strcmp(word, "mcr") == 0) {
                   reading_macro = 1;
                   key = get_word(line, " ,;.\t\n");
                   start_idx = line_count +1;
                   break;
                }
               else {
                   fprintf(new_file, "%s\n", line);
                   break;
               }
           }
           
           else {
               if (strcmp(word, "endmcr") == 0) {
                   struct macro *macro = NULL;
                   macro = create_macro(&macro ,start_idx, (line_count+1));
                   insert_node(host, key, macro);
                   reading_macro = 0;
                   break;
               }
               else { break;}
           }
       }
   }
}



