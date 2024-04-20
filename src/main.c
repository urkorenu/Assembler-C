#include "assembler.h"
#include "linked_list.h"
#include "parser.h"

int
main(int argc, char* argv[])
{
    struct assembler_data assembler;
    char* path;
    int file_count = 1;

    while (file_count < argc) {
        path = argv[file_count++];
        assembler = assembler_init(path);
        parse_pre_processor(&assembler);
        if (!parse_first_phase(&assembler))
            return EXIT_FAILURE;
        if (!parse_second_phase(&assembler))
            return EXIT_FAILURE;
        print_linked_list(&assembler);
        assembler_free(&assembler);
    }
    return EXIT_SUCCESS;
}
