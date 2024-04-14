// second_parse.c

#include "binary_tree.h"
#include "bucket.h"
#include "includes.h"
#include "io.h"
#include "linked_list.h"
#include "parser.c"
/* Helper function to recursively print the linked list the entry words*/
static void
_print_entry_linked_list(const struct linked_list* p,
                         FILE* file,
                         const char* sep)
{
    if ((p->state == DATA_SET)&&להוסיף תנאי שזה אנטרי  {
        /*encrypt_binary(get_lnode_data(p, int), file);*/
        int_to_binary(get_lnode_data(p, int), file);
    }
    if (p->next != NULL) {
        fprintf(file, "%s", sep);
        _print_linked_list(p->next, file, sep);
    }
    return;
}

// fill the linked list when there is a 0 cell
void
fill_when_zero(struct linked_list* head)
{
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

int
parse_second_phase(struct assembler_data* assembler, FILE* source_file)
{
    char line[MAXWORD];
    char* key = NULL;
    int idx = 0;
    int* idx_ptr = &idx;
    char* word = NULL;
    char* symbol = NULL;
    int code;
    int reading_symbol = 0;
    int i = 0;
    int ic;
    struct bucket* data;
    int entry_flag = 0;
    struct line_data* inst = NULL;
    struct linked_list* entry_array;
    struct linked_list* extern_array;
    FILE* ob_file, en_file;
    assembler->ic = 100;
    while (get_line(line, source_file) != NULL) {
        inst = init_instruction(inst);
        word = get_word(line, idx_ptr);
        if (is_symbol(word)) {
            word = get_word(line, idx_ptr);
        }

        else if ((is_data_store_instruction(word)) ||
                 ((strcmp(word, ".extern") == 0))) {
            continue; // Move to the next iteration of the loop
        }
        word = get_word(line, idx_ptr);
        if ((strcmp(word, ".entry") == 0)) {
            if ((data = (get_data_by_key(assembler->symbol_table, word)))) {
                if ((ic = atoi(data->key)))
                    insert_ll_node(entry_array,
                                   create_bucket(word, int_to_voidp(ic)));

            } else {
                // if the symbol not exist it the table
                print_in_error(ERROR_CODE_29);
            }
        }

        if (is_symbol(word)) {
            // if the symbol is not found in the table
            if ((word = get_data_by_key(assembler->symbol_table, word)) ==
                NULL) {
                print_in_error(ERROR_CODE_29);
            } else {
                code |= add_bits(sourch_code, 3, 0);
                fill_when_zero();
            }
            return 1;
        }
        if (entry_flag == 1) {
            en_file = fopen(assembler->as_files->entries_path, "w");
        }
        {
            //-להדפיס את המערך להדפיס קובץ אנטרי- גם ראיתי שיש פונקציה
            // להדפסה לקובץ
        }
        // להדפיס לקבצים- במידה ויש את השתנים
        word = NULL;
        symbol = NULL;
        idx = 0;
        memset(line, 0, MAXWORD);
        reading_symbol = 0;
        inst = NULL;
    }
}
