#include "binary_tree.h"
#include "bucket.h"
#include "files.h"
#include "linked_list.h"
#include "parser.h"

int
main(int argc, char* argv[])
{
    struct linked_list errors, object_list;
    struct binary_tree symbol_table, macro_tree;
    struct files as_files;
    struct assembler_data assembler = {
        .errors = &errors,
        .object_list = &object_list,
        .symbol_table = &symbol_table,
        .macro_tree = &macro_tree,
        .as_files = &as_files,
    };
    char* path;
    FILE* original_file;
    FILE* processed_file;
    int file_count = 1;
    macro_tree.root = NULL;

    while (file_count < argc) {
        path = argv[file_count++];
        set_file_pack(&as_files, path);
        original_file = fopen(as_files.assembly_path, "r");
        processed_file = fopen(as_files.processed_path, "w");
        if (original_file == NULL) {
            fprintf(stderr, "Error opening file %s: ", as_files.assembly_path);
            perror("");
            continue;
        }
        parse_pre_processor(
          original_file, assembler.macro_tree, processed_file);
        fclose(processed_file);
        processed_file = fopen(as_files.processed_path, "r");
        if (parse_first_phase(&assembler, processed_file, &as_files)) {
        } /* second phase here */;
        fclose(original_file);
        fclose(processed_file);
        free_tree(macro_tree.root);
    }

    return 0;
}
