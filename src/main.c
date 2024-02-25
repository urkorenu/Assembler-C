#include "binary_tree.h"
#include "macro.h"

int main(void)
{
    struct binary_tree tree = {0};  
    struct macro *macro = NULL;
    struct macro *data = NULL;
    create_macro(macro, 2, 4, "path");
    insert_node(tree, "test", "data");
    data = get_data_by_key(tree, "test");
    printf("%s\n" ,data->file);
    return 0;
}
