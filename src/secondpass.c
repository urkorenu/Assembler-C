
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "parser.h"
#include "parser.c"
#include "linked_list.h"
#include "Errors.h"

second_parse(struct assembler_data* assembler, FILE* source_file)
{
    int dc = 100;
    int ic = 0;
    char line[MAXWORD];
    char* key = NULL;
    int idx = 0;
    int* idx_ptr = &idx;
    char* word = NULL;
    char* symbol = NULL;
    int reading_symbol = 0;
    FILE* obj_file = fopen(assembler->as_files->object_path, "w");
    while (get_line(line, source_file) != NULL) {
        word = get_word(line, idx_ptr);
        key = get_word(line, idx_ptr);
          if ((strcmp(word, ".data") == 0) || (strcmp(word, ".string") == 0)||(strcmp(word, ".extern") == 0)){
              while (get_line(line, source_file) != NULL) {
              word = get_word(line, idx_ptr);
              }
              {
                 if((strcmp(word, ".entry") == 0)){
                    /*check if its appears once*/
                     if (!get_data_by_key(assembler->symbol_table, symbol)) {
                     create_bucket(symbol_data, word, .entry);
                    insert_node(assembler->symbol_table, key, symbol_data);
                    break;
                ic++;
                    
                }
                else{
                    code operands!
                }
       ic = ic+L; 
       break; 
              }
              if (error !==null){
                exit(EXIT_FAILURE);
              }
}
int print_externals(struct assembler_data* assembler, FILE* source_file , symbol_table *EXTERNAL, int *IC ){
      
    int i, j, found, empty;
    char *temp;
if ( ssembler->symbol_table.EXTERNAL !=NULL){
    /* Open a new external file with the '.ext' extension */
    fp = fopen((temp = add_new_file(file_name, ".ext")), "w");

    /* Initialize the 'empty' flag to 1, assuming no extern labels are found initially */
    empty = 1;

    /* Check if the file was opened successfully */
    if (source_file == NULL) {
        print_in_error(ERROR_CODE_7);
       
}
symbol_table *current = assembler->EXTERNAL
    // Iterate through the linked list
    while (current != NULL) {
        printf("%s\n", current->symbol_table.EXTERNAL); // Print the label of the current node
        current = current->next; // Move to the next node
    }
                        /* Set 'empty' to 0 to indicate at least one extern label is found*/
                    empty = 0;
                }
            }
        }
    }
    fclose(fp);

    /* If no extern labels are found, remove the temporary file and free the memory */
    if (empty) {
        remove(temp);
    }
}
char *add_new_file(char *source_file, char *ending) {
    char *c, *new_file_name;
    new_file_name = malloc(MAX_LEN  * sizeof(char));
    strcpy(new_file_name, file_name);
    /* deleting the file name if a '.' exists and forth */
    if ((c = strchr(new_file_name, '.')) != NULL) {
        *c = '\0';
    }
    /* adds the ending of the new file name */
    strcat(new_file_name, ending);
    return new_file_name;
}
//need to do more for all kinds of text files 
