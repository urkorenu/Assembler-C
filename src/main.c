#include "binary_tree.h"
#include "io.h"
#include "parser.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *file_path;
  char *new_path;
  FILE *file;
  FILE *new_file;
  int file_count = 1;
  struct binary_tree tree;
  tree.root = NULL;

  while (file_count < argc) {
    file_path = argv[file_count++];
    file = fopen(file_path, "r");
    new_path = modify_path(file_path);
    new_file = fopen(new_path, "w");
    if (file == NULL) {
      fprintf(stderr, "Error opening file %s: ", file_path);
      perror("");  
      continue;
    }

    parse_pre_processor(file, &tree, new_file);
    fclose(file);
    fclose(new_file);
    free_tree(tree.root);
  }

  return 0;
}
