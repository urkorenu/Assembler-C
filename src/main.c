#include "assembler.h"
#include "linked_list.h"
#include "parser.h"

int
main(int argc, char* argv[])
{
    struct assembler_data assembler;
    char* path;
    int is_valid = EXIT_SUCCESS;
    int file_count = 1;

    while (file_count < argc) {
        path = argv[file_count++];
        assembler = assembler_init(path);
        parse_pre_processor(&assembler);
        if (parse_first_phase(&assembler) == is_valid) {
            if (parse_second_phase(&assembler) == is_valid) {
                print_linked_list(&assembler);
            } else {
                is_valid = EXIT_FAILURE;
            }
        } else {
            is_valid = EXIT_FAILURE;
        }
        /* assembler_free(&assembler); */
    }
    return is_valid;
}
