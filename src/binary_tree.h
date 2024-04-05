#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "bucket.h"
#include "includes.h"

/*
 * General Binary Tree -
 *
 *  Structs
 *  */

struct tnode {
    struct bucket* node;
    struct tnode* left_node;
    struct tnode* right_node;
};

struct binary_tree {
    struct tnode* root;
};

/*
 * Methods
 *
 *  Get -
 * */

extern struct tnode*
find_previous_node(struct tnode* p, char* key);

extern struct tnode*
find_node(struct binary_tree* tree, char* key);

extern void*
get_data_by_key(struct binary_tree* tree, char* key);

/*
 * Set -
 * */

extern int
insert_node(struct binary_tree* tree, char* key, void* data);

extern struct tnode*
add_node(struct tnode* p, char* key, void* data);

extern struct tnode*
create_tnode(struct tnode* p, char* key, void* data);

/*
 * Memory allocation -
 */

extern struct binary_tree*
btree_alloc(void);

extern struct binary_tree*
create_new_btree(void);

extern void
btree_free(struct binary_tree* btree);

extern void
free_tree(struct tnode* p);

extern void
treeprint(struct tnode* p);

#endif /* _BINARY_TREE_H */
