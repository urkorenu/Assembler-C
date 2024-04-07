#include "binary_tree.h"
#include "bucket.h"

/*/////////////////////////////////////////*/
/* ///// Binary tree node functions ///////*/
/*/////////////////////////////////////////*/

/* Static functions */

/* Allocate memory for a new tree node */
static struct tnode*
tree_alloc(void)
{
    return (struct tnode*)malloc(sizeof(struct tnode));
}

/* Find a node with the given key in the binary tree */
static struct tnode*
_find_node(struct tnode* root, const char* key)
{

    if (root == NULL || root->node == NULL) {
        return NULL;
    }
    int cmp  = strcmp(root->node->key, key);
    if (cmp == 0) {
        return root;
    }
    if (cmp > 0)
        return _find_node(root->right, key);
    else
        return _find_node(root->left, key);
}

/* Get methods */

/* Find the previous node of a given key in the binary tree */
struct tnode*
find_previous_node(struct tnode* root, const char* key)
{
    if (root->left == NULL || root->right== NULL || root->left == NULL)
        return NULL;
    int cmp = strcmp(root->right->node->key, key);
    if (cmp > 0) {
        if (strcmp(root->right->node->key, key) == 0)
            return root;
        return find_previous_node(root->right, key);
    } else {
        if (strcmp(root->left->node->key, key) == 0)
            return root;

        return find_previous_node(root->left, key);
    }
}

/* Get data associated with the given key from the binary tree */
void*
get_data_by_key(struct binary_tree* tree, const char* key)
{
    struct tnode* node = _find_node(tree->root, key);
    if (node != NULL && node->node != NULL && node->node->data != NULL) {
        return node->node->data;
    } else {
        return NULL;
    }
}

/* Print binary tree by its key and ic - suited for symbol table */
void
treeprint(struct tnode* p)
{

    if (p != NULL) {
        treeprint(p->left);
        printf("key : %s, ", p->node->key);
        struct bucket* temp_buck = p->node->data;
        printf("ic : %d", (int)temp_buck->data);
        printf("\n");
        treeprint(p->right);
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
        root = create_tnode(key, data);}
    else {
        int cmp = strcmp(key, root->node->key);
    if (cmp == 0) {
        root = create_tnode(key, data);
    } 
    else if (cmp > 0)
        root->left = add_node(root->left, key, data);
    else
        root->right = add_node(root->right, key, data);}
    return root;
}


/* Create a new tree node with the given key and data */
struct tnode*
create_tnode(const char* key, void* data)
{
    struct tnode* node = tnode_alloc();
    if (node != NULL) {
        node->node = create_bucket(key, data);
        node->left = NULL;
        node->right = NULL;
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

