#include "binary_tree.h"
#include "bucket.h"
#include <string.h>

static struct tnode*
tree_alloc(void);

static struct tnode*
_find_node(struct tnode* p, char* key)
{
    int cmp;

    if (p == NULL || p->node == NULL) {
        return NULL;
    }
    if ((cmp = strcmp(p->node->key, key)) == 0) {
        return p;
    }
    if (cmp > 0)
        return _find_node(p->right_node, key);
    else
        return _find_node(p->left_node, key);
}

struct tnode*
find_node(struct binary_tree* tree, char* key)
{
    return _find_node(tree->root, key);
}

struct tnode*
find_previous_node(struct tnode* p, char* key)
{
    int cmp;

    if (p->left_node == NULL || p->right_node == NULL)
        return NULL;
    cmp = strcmp(p->right_node->node->key, key);
    if (cmp > 0) {
        if ((cmp = strcmp(p->right_node->node->key, key)) == 0)
            return p;
        return find_previous_node(p->right_node, key);
    } else {
        if ((cmp = strcmp(p->left_node->node->key, key)) == 0)
            return p;

        return find_previous_node(p->left_node, key);
    }
}

int
insert_node(struct binary_tree* tree, char* key, void* data)
{
    if (tree->root != NULL) {
        tree->root = add_node(tree->root, key, data);
    } else
        tree->root = add_node(NULL, key, data);
    return 1;
}

struct tnode*
add_node(struct tnode* p, char* key, void* data)
{
    int cond;

    if (p == NULL) {
        p = create_tnode(p, key, data);
    } else if ((cond = strcmp(key, p->node->key)) == 0) {
        p = create_tnode(p, key, data);
    } else if (cond < 0)
        p->left_node = add_node(p->left_node, key, data);
    else
        p->right_node = add_node(p->right_node, key, data);
    return p;
}

struct tnode*
create_tnode(struct tnode* p, char* key, void* data)
{
    p = tree_alloc();
    p->node = create_bucket(key, data);
    p->left_node = p->right_node = NULL;
    return p;
}

void*
get_data_by_key(struct binary_tree* tree, char* key)
{
    struct tnode* p = find_node(tree, key);
    if (p != NULL && p->node != NULL && p->node->data != NULL) {
        return p->node->data;
    } else {
        return NULL;
    }
}

static struct tnode*
tree_alloc(void)
{
    return (struct tnode*)malloc(sizeof(struct tnode));
}

struct binary_tree*
btree_alloc(void)
{
    struct binary_tree *btree = NULL;

    btree = malloc(sizeof(struct binary_tree));
    btree->root = NULL;
    return btree;
}

struct binary_tree*
create_new_btree(void)
{
    return btree_alloc();
}

void
btree_free(struct binary_tree* btree)
{
    if (btree == NULL)
        return;
    free_tree(btree->root);
    free(btree);
    btree = NULL;
}

void
free_tree(struct tnode* p)
{
    if (p != NULL) {
        free_tree(p->left_node);
        free_tree(p->right_node);
        free_bucket(p->node);
        free(p);
    }
}
