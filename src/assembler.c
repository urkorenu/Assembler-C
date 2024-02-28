#include "binary_tree.h"
#include "macro.h"

/* Test to check if the data structers are working good */

int main(void)
{
    printf("tree created");
    struct binary_tree tree;
    tree.root = NULL;
    printf("tree created");
    struct macro *macro = NULL;
    printf("macro created");
    struct macro *data = NULL;
    create_macro(macro, 2, 4, "path");
    printf("%d\n", macro->start);
    insert_node(tree, "test", "data");
    data = get_data_by_key(tree, "test");
    printf("%s\n" ,data->file);
    return 0;
}
