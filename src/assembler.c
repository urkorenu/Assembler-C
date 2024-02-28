#include "binary_tree.h"
#include "macro.h"

/* Test to check if the data structers are working good */

int main(void)
{
    printf("tree created\n");
    struct binary_tree *tree = NULL;
    struct macro *macro = NULL;
    printf("macro created\n");
    struct macro *data = NULL;
    char *key = malloc(sizeof(char) * (strlen("key") + 1)); 
    strcpy(key, "key");
    macro = create_macro(&macro, 2, 4);
    printf("macro node created\n");
    insert_node(tree, key, &macro); 
    printf("tree node created\n");
    printf("%s\n", tree->root->node->key);
    data = get_data_by_key(tree, key);
    printf("got data by key\n");
    printf("%d\n" ,data->start);

    return 0;
}
