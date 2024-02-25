#include "binary_tree.h"


static  struct tnode *_find_node(struct tnode *p, char *key) 
{
    int cmp;

    if (p == NULL)
        return p;
    if ((cmp = strcmp(p->node->key, key)) == 0)
        return p;
    if (cmp > 0)
        return _find_node(p->right_node , key);
    else 
        return _find_node(p->left_node , key);

}

struct tnode *find_node(struct binary_tree tree, char *key)
{
    if (!key)
        return NULL;
    return _find_node(tree.root, key);
    
}

int insert_node(struct binary_tree tree, char *key, void *data)
{
    struct tnode *node = find_node(tree, key);
    
    if (node == NULL) {
        printf("Invalid key");
        return 0; }
    node = create_tnode(node, key, data);
    return 1;
}

int remove_node(struct binary_tree tree, char *key) 
{
    struct tnode *p = find_node(tree, key);
    if (!(p->node->key)) {
        printf("No matching node");
        return 0; }
    p = NULL; 
    return 1; 
}

struct tnode *create_tnode(struct tnode *p, char *key, void *data) 
{
    p = tree_alloc(key, data);
    p->node->key = key;
    p->node->data = data;
    p->left_node = p->right_node = NULL;
    return p;
}

void *get_data_by_key(struct binary_tree tree, char *key) 
{
    struct tnode *p = find_node(tree, key);
    return p->node->data;

}

struct tnode *tree_alloc(void *key, void *data)
{
  return (struct tnode *)malloc(sizeof(struct tnode));
}


void free_tree(struct tnode *p)
{
  if (p != NULL) {
    free_tree(p->left_node);
    free_tree(p->right_node);
    free(p->node->key);
    free(p->node->data);
    free(p);
  }
}

