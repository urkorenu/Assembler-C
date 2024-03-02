#include "binary_tree.h"
#include "macro.h"

/* Test to check if the data structers are working good */

int main(void)
{
    struct binary_tree tree ;
    tree.root = NULL;
    struct macro *macro = NULL;
    struct macro *data = NULL;
    char *key = malloc(sizeof(char) * (strlen("some key") + 1)); 
    strcpy(key, "some key");
    macro = create_macro(&macro, 12, 4);
    insert_node(&tree, key, macro); 
    printf("%s\n", tree.root->node->key);
    data = get_data_by_key(&tree, key);
    printf("%d\n" ,data->start);
    free_tree(tree.root);
    free(key);

    return 0;
}
