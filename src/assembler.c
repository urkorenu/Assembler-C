#include "include/assembler.h"
#include "include/binary_tree.h"
#include "include/error.h"
#include "include/files.h"
#include "include/io.h"
#include "include/linked_list.h"
#include "include/parser.h"

const char ASSEMBLER_MEM_ERR[] = {
    "FATAL ERROR: Failed to allocate memory for struct assembler_data\n"
};

int
parse_first_phase(struct assembler_data* assembler)
{
    char line[MAXWORD]; /* Buffer to store each line of the source file. */
    int idx = 0; /* Index to track the current position in the line buffer. */
    char word[MAXWORD];
    char symbol[MAXWORD];
    int reading_symbol = 0;
    int reading_data = 0;
    int is_valid = 1;
    int line_counter = 0;
    FILE* source_file;

    source_file = verbose_fopen(assembler->as_files->processed_path, "r");

    if (!source_file) {
        print_in_error(FAILED_OPEN_READING, 0, NULL);
        return 0;
    }

    while (get_line(line, source_file) != NULL) {
        if (!line[0])
            continue;
        if (is_comment(line))
            continue;
        line_counter++;
        get_word(line, &idx, word);

        if (strcmp(word, ".define") == 0) {
            is_valid = parse_define(assembler, line, &idx, line_counter);

        } else if (is_symbol(word)) {
            int temp_index = 0;
            get_word(word, &temp_index, symbol);
            get_word(line, &idx, word);
            reading_symbol = 1;
        }

        if (is_data_store_instruction(word)) {
            is_valid = parse_data_store_instruction(assembler,
                                                    line,
                                                    word,
                                                    &reading_symbol,
                                                    &reading_data,
                                                    symbol,
                                                    &idx,
                                                    line_counter);
        }
        if (is_e_instruction(word)) {
            if (strcmp(word, ".extern") == 0) {
                is_valid = parse_extern(assembler, line, &idx, line_counter);
            }

        } else {
            is_valid = parse_instruction(assembler,
                                         line,
                                         &idx,
                                         reading_data,
                                         reading_symbol,
                                         symbol,
                                         &line_counter,
                                         word,
                                         line_counter);
        }
        idx = 0;
        memset(line, 0, MAXWORD);
        reading_symbol = 0;
        reading_data = 0;
    }
    fclose(source_file);
    return is_valid;
}

int
parse_second_phase(struct assembler_data* assembler)
{
    int is_valid = 1;
    int node_ic = 100;
    char line[MAXWORD];
    int line_counter = 0;
    int entry_flag, extern_flag = 0;
    struct linked_list* last_unset_node;
    FILE *en_file, *ex_file, *source_file;
    struct linked_list* entry_list = create_new_ll_node(0);
    struct linked_list* extern_list = create_new_ll_node(0);

    assembler->ic = 100;
    last_unset_node = get_first_unset_node(assembler->object_list, &node_ic);
    source_file = fopen(assembler->as_files->processed_path, "r");

    if (!source_file)
        return 0;

    while (get_line(line, source_file) != NULL) {
        if (!line[0])
            continue;
        if (is_comment(line))
            continue;
        line_counter++;
        is_valid &= process_line(assembler,
                                 line,
                                 &line_counter,
                                 entry_list,
                                 &entry_flag,
                                 extern_list,
                                 &extern_flag,
                                 last_unset_node,
                                 &node_ic);
        node_ic = 100;
        last_unset_node =
          get_first_unset_node(assembler->object_list, &node_ic);
    }
    memset(line, 0, MAXWORD);

    if (entry_flag == 1 && is_valid) {
        en_file = fopen(assembler->as_files->entries_path, "w");
        if (en_file) {
            print_e_list(entry_list, en_file, "\n");
            printf("entry file was created successfully\n");
            fclose(en_file);
            en_file = NULL;
        }
    }
    if (extern_flag == 1 && is_valid) {
        ex_file = fopen(assembler->as_files->externals_path, "w");
        if (ex_file) {
            print_e_list(extern_list, ex_file, "\n");
            printf("extern file was created successfully\n");
            fclose(ex_file);
            ex_file = NULL;
        }
    }

    llfree(entry_list, 1);
    llfree(extern_list, 1);
    fclose(source_file);
    return is_valid;
}

struct assembler_data*
assembler_alloc(void)
{
    struct assembler_data* assembler = malloc(sizeof(struct assembler_data));

    if (assembler == NULL) {
        fprintf(stderr, ASSEMBLER_MEM_ERR);
        return NULL;
    }
    return assembler;
}
void
assembler_free(struct assembler_data* assembler)
{
    if (assembler == NULL)
        return;

    llfree(assembler->object_list, 0);
    btree_free(assembler->symbol_table);
    btree_free(assembler->macro_tree);
    files_free(assembler->as_files);
    memset(assembler, 0, sizeof(struct assembler_data));
}

struct assembler_data
assembler_init(char* path)
{
    struct assembler_data assembler;
    assembler.object_list = create_new_ll_node(0);
    assembler.symbol_table = create_new_btree();
    assembler.macro_tree = create_new_btree();
    assembler.as_files = files_alloc();
    assembler.ic = 100;
    assembler.instruction_c = 0;
    assembler.data_c = 0;
    set_file_pack(assembler.as_files, path);
    return assembler;
}
