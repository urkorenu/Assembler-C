#include "binary_tree.h"
#include "bucket.h"
#include <string.h>

static struct tnode *tree_alloc(void);

static  struct tnode *_find_node(struct tnode *p, char *key) 
{
    int cmp;

    
    if (p == NULL || p->node == NULL) {
        return p;}
    if ((cmp = strcmp(p->node->key, key)) == 0){
        return p;}
    if (cmp > 0)
        return _find_node(p->right_node , key);
    else 
        return _find_node(p->left_node , key);

}

struct tnode *find_node(struct binary_tree *tree, char *key)
{
    return _find_node(tree->root, key);
}

int insert_node(struct binary_tree *tree, char *key, void *data)
{
    if (tree->root != NULL) {
        tree->root = add_node(tree->root, key, data);
    }
    else 
        tree->root = add_node(NULL , key, data);
    return 1;
}

struct tnode *add_node(struct tnode *p, char *key, void *data) {
    int cond;

    if (p == NULL) {
        p = create_tnode(p, key, data); }
    else if ((cond = strcmp(key, p->node->key)) == 0) {
        p = create_tnode(p, key, data); }
    else if (cond < 0)
        p->left_node = add_node(p->left_node, key, data);
    else
        p->right_node = add_node(p->right_node, key, data);
    return p;
}


struct tnode *create_tnode(struct tnode *p, char *key, void *data) 
{
    p = tree_alloc();
    p->node = create_bucket(p->node, key, data);
    p->left_node = p->right_node = NULL;
    return p;
}

int remove_node(struct binary_tree *tree, char *key) 
{
    struct tnode *p = find_node(tree, key);
    if (!(p->node->key)) {
        return 0; }
    p = NULL; 
    return 1; 
}


void *get_data_by_key(struct binary_tree *tree, char *key) {
    struct tnode *p = find_node(tree, key);
    if (p != NULL && p->node != NULL && p->node->data != NULL) {
        return p->node->data;
    } else {
        return NULL;
    }
}



static struct tnode *tree_alloc(void)
{
  return (struct tnode *)malloc(sizeof(struct tnode));
}


void free_tree(struct tnode *p)
{
  if (p != NULL) {
    free_tree(p->left_node);
    free_tree(p->right_node);
    free_bucket(p->node);
    free(p);
  }
}



