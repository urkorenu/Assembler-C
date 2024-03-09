#include "binary_tree.h"
#include "parser.h"
#include "files.h"

int main(int argc, char *argv[]) {
  char *path;
  FILE *file;
  FILE *new_file;
  int file_count = 1;
  struct binary_tree tree;
  tree.root = NULL;
  struct files as_files;

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

    parse_pre_processor(file, &tree, new_file);
    parse_first_phase(new_file, &tree, new_file);
    fclose(file);
    fclose(new_file);
    free_tree(tree.root);
  }

  return 0;
}
