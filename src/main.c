#include "binary_tree.h"
#include "files.h"
#include "linked_list.h"
#include "parser.h"

int main(int argc, char *argv[]) {
  struct assembler_data assembler;
  struct linked_list errors, object_list;
  struct binary_tree symbol_table, macro_tree;
  struct files as_files;
  assembler.errors = &errors;
  assembler.object_list = &object_list;
  assembler.symbol_table = &symbol_table;
  assembler.macro_tree = &macro_tree;
  assembler.as_files = &as_files;
  char *path;
  FILE *file;
  FILE *new_file;
  int file_count = 1;
  macro_tree.root = NULL;

  while (file_count < argc) {
    path = argv[file_count++];
    set_file_pack(&as_files, path);
    file = fopen(as_files.assembly_path, "r");
    new_file = fopen(as_files.processed_path, "w");
    if (file == NULL) {
      fprintf(stderr, "Error opening file %s: ", as_files.assembly_path);
      perror("");
      continue;
    }

    parse_pre_processor(file, assembler.macro_tree, new_file);
    parse_first_phase(&assembler, new_file);
    fclose(file);
    fclose(new_file);
    free_tree(macro_tree.root);
  }

  return 0;
}
