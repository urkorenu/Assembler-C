//second_parse.c 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linked_list.h"
#include "parser.c"

int parse_second_phase(struct assembler_data* assembler,FILE* source_file, struct files* as_files)
{
    char line[MAXWORD];
    char* key = NULL;
    int idx = 0;
    int* idx_ptr = &idx;
    char* word = NULL;
    char* symbol = NULL;
    char*  search_word ;
    int reading_symbol = 0;
    int i=0;
    int entry_flag =0
    assembler->ic = 100;
    struct line_data* inst = NULL;
    char* entry_array[MAXWORD]= {0};
    while (get_line(line, source_file) != NULL) {
        inst = init_instruction(inst);
        word = get_word(line, idx_ptr);
        if (is_symbol(word)) {
         word = get_word(line, idx_ptr); 
        }

            else if((is_data_store_instruction(word))||((is_e_instruction(word))&&(strcmp(word, ".extern") == 0))){
                  if (get_line(line, source_file) == NULL) {
                // Handle end of file or error
                break;
            }
            continue; // Move to the next iteration of the loop
        }
        word = get_word(line, idx_ptr);
        if((is_e_instruction(word))&&(strcmp(word, ".entry") == 0))
        {
            search_word = word;
                    if ((search_word = get_data_by_key(assembler->symbol_table, search_word)) != NULL) {
                        entry_array[i] = search_word;
                        entry_flag = 1;
                        i++;

                    }
                        else
                        {
                           print_in_error(ERROR_CODE_29);
                        }
        }
        \\לקודד עם הפונקציה של אור 
           if (is_symbol(word)) {
            search_word = word;
            //if the symbol is not found in the table
            if ((search_word = get_data_by_key(assembler->symbol_table, search_word)) = NULL) {
                print_in_error(ERROR_CODE_29);
            else
            {
//--פונקציה של אור - לקחת את הערך מהטבלה ולקודד לבינרי
            }
            if (entry_flag=1 )
            {
               //-להדפיס את המערך להדפיס קובץ אנטרי- גם ראיתי שיש פונקציה להדפסה לקובץ 
            }
            //להדפיס לקבצים- במידה ויש את השתנים



        

            