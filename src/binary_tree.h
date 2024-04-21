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
    struct tnode* left;
    struct tnode* right;
};

struct binary_tree {
    struct tnode* root;
};

/*
 * Methods
 *
 *  Get -
 * */

struct tnode
tnode_init(void);

/**
 * @brief This function finds the previous node of a given key in a binary tree.
 * @param root The root node of the binary tree.
 * @param key The key to find the previous node for.
 * @return Returns a pointer to the previous node of the given key if found, otherwise returns NULL.
 */  
extern struct tnode*
find_previous_node(struct tnode* root, const char* key);

/**
 * @brief This function retrieves data associated with the given key from a binary tree.
 * @param tree The binary tree containing the data.
 * @param key The key to search for in the binary tree.
 * @return Returns a pointer to the data associated with the given key if found, otherwise returns NULL.
 */ 
extern void*
get_data_by_key(struct binary_tree* tree, const char* key);

extern void
treeprint(struct tnode* p);

/*
 * Set -
 * */

extern int
insert_node(struct binary_tree* tree, const char* key, void* data);

extern struct tnode*
add_node(struct tnode* p, const char* key, void* data);

extern struct tnode*
create_tnode(const char* key, void* data);

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

#endif /* _BINARY_TREE_H */
