#include "binary_tree.h"
#include "files.h"
#include "linked_list.h"
#include "parser.h"

int
main(int argc, char* argv[])
{
    struct files as_files;
    struct assembler_data* assembler;
    assembler = assembler_init();
    char* path = NULL
      ;
    FILE* original_file;
    FILE* processed_file;
    int file_count = 1;

    while (file_count < argc) {
        path = argv[file_count++];
        set_file_pack(assembler->as_files, path);
        original_file = fopen(assembler->as_files->assembly_path, "r");
        processed_file = fopen(assembler->as_files->processed_path, "w");
        if (original_file == NULL) {
            fprintf(stderr, "Error opening file %s: ", assembler->as_files->assembly_path);
            perror("");
            continue;
        }
        parse_pre_processor(
          original_file, assembler->macro_tree, processed_file);
        fclose(processed_file);
        processed_file = fopen(assembler->as_files->processed_path, "r");
        if (parse_first_phase(assembler, processed_file, &as_files)) {
        } /* second phase here */;
        fclose(original_file);
        fclose(processed_file);
    }

    return 0;
}
