#include "binary_tree.h"
#include "bucket.h"
#include "includes.h"
#include "instruction.h"
#include "io.h"
#include "macro.h"
#include "parser.h"

static int is_data_store_instruction(char *word)
{
    if (strcmp(word, ".data") == 0)
        return 1;
    else if (strcmp(word, ".string") == 0)
        return 1;
    return 0;
}

static int is_symbol(char *word)
{
    int length = strlen(word);
    if (word[length-1] == ':')
        return 1;
    return 0;
}

static int is_e_instruction(char *word)
{
    if (strcmp(word, ".extern") == 0)
        return 1;
    else if (strcmp(word, ".entry") == 0)
        return 1;
    return 0;
}


void parse_pre_processor(FILE *file, void *host, FILE *new_file)
{
   int line_count = 1;
   char line[MAXWORD];
   char *key = NULL;
   int idx = 0;
   int *idx_ptr = &idx;
   char *word = NULL;
   int reading_macro = 0;
   int start_idx;
   struct macro *temp = NULL;
   fpos_t temp_pos;


   while (get_line(line, file) != NULL) {
       while ((word = get_word(line, idx_ptr))) {
           if (!reading_macro) {
               if (strcmp(word, "mcr") == 0) {
                   reading_macro = 1;
                   key = get_word(line, idx_ptr);
                   start_idx = ++line_count;
                   fgetpos(file, &temp_pos);
                   break;
                }
               else {
                   temp = get_data_by_key(host, word);
                   if (temp ) {
                       fgetpos(file, &temp_pos);
                       insert_macro(temp, file, new_file);
                       fsetpos(file, &temp_pos);
                       ++line_count;
                       break;
                    }
                   else {
                        fprintf(new_file, "%s", line);
                        ++line_count;
                        break;
                   }
               }
           }
           
           else {
               if (strcmp(word, "endmcr") == 0) {
                   struct macro *macro = NULL;
                   macro = create_macro(&macro , temp_pos , line_count - start_idx);
                   insert_node(host, key, macro);
                   reading_macro = 0;
                   break;
               }
               else {
                   line_count++;
                   break;}
           }
       }
       word = NULL;
       idx = 0;
       memset(line, 0, MAXWORD);
   }
}

struct bucket *parse_first_phase(FILE *file, void *host, FILE *new_file)
{
   int line_count = 1;
   int dc = 100;
   int ic = 100;
   char line[MAXWORD];
   char *key = NULL;
   int idx = 0;
   int *idx_ptr = &idx;
   char *word = NULL;
   char *symbol = NULL;
   int reading_symbol = 0;
   int start_idx;
   fpos_t temp_pos;
   struct bucket *error = NULL;
   char error_data[MAXWORD];
   struct bucket *symbol_data = NULL;
   struct instruction *inst = NULL;
   init_instruction(inst);

   while (get_line(line, file) != NULL) {
       word = get_word(line, idx_ptr);

       if (strcmp(word, ".define") == 0){
           key = get_word(line, idx_ptr);
           if (!get_data_by_key(host, key)){
                   word = get_word(line, idx_ptr);
                   if (strcmp(word, "=") == 0){
                        word = get_word(line, idx_ptr);
                       create_bucket(symbol_data, word, MDEFINE);
                        /* maybe need conversion to int or else */
                        insert_node(host, key, symbol_data);
                        ++ic;
                   }
                   else {
                       strcpy(error_data, "invalid syntax");
                       /* maybe i dont need to create bucket for every error
                        * or should i create tree of error ?! */
                        create_bucket(error, key, error_data);
                   }


           }
           else {
                strcpy(error_data, "define key is already initialized");
               create_bucket(error, key, error_data);
           }
       }           
       else if (is_symbol(word)){
               strcpy(symbol, word);
               word = get_word(line, idx_ptr);
               reading_symbol = 1;
       }

       if (is_data_store_instruction(word)){
           if (reading_symbol){
               if (!get_data_by_key(host, symbol)){
                   create_bucket(symbol_data, DATA, to_void_ptr(dc));
                   dc++;
                    /* maybe need conversion to int or else */
                    insert_node(host, symbol, symbol_data);
                    /* process functions */
                }
               else {
                    strcpy(error_data, "symbol is already initialized");
                   create_bucket(error, key, error_data);
                }
           }
       }
       if (is_e_instruction(word)) {
            if (strcmp(word, ".extern") == 0) {
                key = get_word(line, idx_ptr);
                create_bucket(symbol_data, NULL, EXTERNAL);
                insert_node(host, key, symbol_data);
                ic++;
            }
        }
       else {
            if (reading_symbol){
               if (!get_data_by_key(host, symbol)){
                    create_bucket(symbol_data, CODE, to_void_ptr(dc));
                    ic++;
                    /* maybe need conversion to int or else */
                    insert_node(host, symbol, symbol_data);
               }
               else {
                    strcpy(error_data, "symbol is already initialized");
                   create_bucket(error, key, error_data);
                }
            }
            if (get_instruction(inst, word)){
                ic = ic + inst->args;
            }
            /* process commands */

       }
       word = NULL;
       symbol = NULL;
       idx = 0;
       memset(line, 0, MAXWORD);
       reading_symbol = 0;
       
   }
   return error;

}


