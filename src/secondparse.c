//second_parse.c 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linked_list.h"
#include "parser.c"
/* Helper function to recursively print the linked list the entry words*/
static void
_print_linked_list(const struct linked_list* p, FILE* file, const char* sep)
{
    if ((p->state == DATA_SET)&&להוסיף תנאי שזה אנטרי  {
        /*encrypt_binary(get_lnode_data(p, int), file);*/
        int_to_binary(get_lnode_data(p, int), file);
    }
    if (p->next != NULL) {
        fprintf(file, "%s", sep);
        _print_linked_list(p->next, file, sep);
    }
}


void fill_when_zero(struct linked_list* head) {
    struct linked_list* current = head;

    // Traverse the linked list
    while (current != NULL) {
        // Check if the current node's data value is 0
        if (current->data == 0) {
            set_data(sourch_code, code);
        }

        // Move to the next node
        current = current->next;
    }
}

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
                            //if the symbol noe exist it the table
                           print_in_error(ERROR_CODE_29);
                        }
        }
        
           if (is_symbol(word)) {
            search_word = word;
            //if the symbol is not found in the table
            if ((search_word = get_data_by_key(assembler->symbol_table, search_word)) = NULL) {
                print_in_error(ERROR_CODE_29);
            else
            {
                int sourch_code = get_data_by_key(assembler->symbol_table, search_word);
                code |= add_bits(sourch_code, 3, 0);
                  fill_when_zero(struct linked_list* head);

            }
     FILE* ob_file = fopen(as_files->object_path, "w");
    print_linked_list(assembler->object_list, ob_file);
    printf("%s", "\nSymbol Table:\n");
    treeprint(assembler->symbol_table->root);
    return 1;
}
            if (entry_flag=1 )
            {
                 FILE* ob_file = fopen(as_files-> .entries_path, "w");
               

            }
            {
               //-להדפיס את המערך להדפיס קובץ אנטרי- גם ראיתי שיש פונקציה להדפסה לקובץ 
            }
            //להדפיס לקבצים- במידה ויש את השתנים



        