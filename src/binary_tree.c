#include "binary_tree.h"
#include "bucket.h"
#include <stdlib.h>

/*/////////////////////////////////////////*/
/* ///// Binary tree node functions ///////*/
/*/////////////////////////////////////////*/

/* Static functions */

struct tnode
tnode_init(void)
{
    struct tnode node;
    node.node = bucket_alloc();
    node.left = NULL;
    node.right = NULL;
    return node;
}

/* Find a node with the given key in the binary tree */
static struct tnode*
_find_node(struct tnode* root, const char* key)
{

    int cmp;
    if (root == NULL) {
        return NULL;
    }
    cmp = strcmp(root->node->key, key);
    if (cmp == 0) {
        return root;
    }
    if (cmp > 0)
        return _find_node(root->right, key);
    else
        return _find_node(root->left, key);
}
/*/////////////*/
/* Get methods */
/*/////////////*/

/* Get data associated with the given key from the binary tree */
void*
get_data_by_key(struct binary_tree* tree, const char* key)
{
    struct tnode* node = _find_node(tree->root, key);
    if (node != NULL) {
        return node->node->data;
    }
    return NULL;
}

/* Print binary tree by its key and ic - suited for symbol table */
void
treeprint(struct tnode* p)
{

    struct bucket* temp_buck;
    if (p != NULL) {
        if (p->node != NULL) {
            temp_buck = p->node->data;
            treeprint(p->left);
            printf("key : %s, ", p->node->key);
            if (temp_buck->data != NULL) {
                printf("ic : %d", ((int*)temp_buck->data)[0]);
            }
            printf("\n");
            treeprint(p->right);
        }
    }
}

/* Set methods */

/* Insert a node with the given key and data into the binary tree */
int
insert_node(struct binary_tree* tree, const char* key, void* data)
{
    if (tree->root != NULL) {
        tree->root = add_node(tree->root, key, data);
    } else
        tree->root = add_node(NULL, key, data);
    return 1;
}

/* Insert a node with the given key and data into the binary tree */
struct tnode*
add_node(struct tnode* root, const char* key, void* data)
{
    if (root == NULL) {
        root = create_tnode(key, data);
    } else {
        int cmp = strcmp(key, root->node->key);
        if (cmp == 0) {
            root = create_tnode(key, data);
        } else if (cmp > 0)
            root->left = add_node(root->left, key, data);
        else
            root->right = add_node(root->right, key, data);
    }
    return root;
}

/* Create a new tree node with the given key and data */
struct tnode*
create_tnode(const char* key, void* data)
{
    struct tnode* node;

    if (!key) {
        fprintf(stderr, "Key is null! (key=%p)\n", (void*)key);
        return NULL;
    }

    node = malloc(sizeof(struct tnode));
    if (node != NULL) {
        node[0] = tnode_init();
        bucket_set_key(node->node, key);
        bucket_set_data(node->node, data);
    }
    return node;
}

/* Free Methods */

/* Free memory allocated for the binary tree and calls for free_tree function */
void
btree_free(struct binary_tree* btree)
{
    if (btree == NULL)
        return;
    free_tree(btree->root);
    free(btree);
    btree = NULL;
}

/* Free memory allocated for the binary tree nodes */
void
free_tree(struct tnode* root)
{
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free_bucket(root->node);
        free(root);
    }
}

struct binary_tree*
btree_alloc(void)
{
    struct binary_tree* btree = NULL;

    btree = malloc(sizeof(struct binary_tree));
    btree->root = NULL;
    return btree;
}

struct binary_tree*
create_new_btree(void)
{
    return btree_alloc();
}
