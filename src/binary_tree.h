#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "bucket.h"
#include "includes.h"

/*
 * General Binary Tree -
 *
 *  Structs
 *  */

struct tnode { /* Node in a binary tree. */
    struct bucket* node; /* Contains key-value pairs or data. */
    struct tnode* left; /* A pointer to the left child node of the current node. */
    struct tnode* right; /* A pointer to the right child node of the current node. */
};

/* This structure represents a binary tree. */
struct binary_tree {
    struct tnode* root; /* Holds a pointer to the root node of the binary tree. */
};
/*
 * Methods
 *
 *  Get -
 * */

/**
 * @brief This function initializes a tree node
 * @return Returns the initialized tree node 
 */  
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

/**
 * @brief This function prints the contents of a binary tree by its key and associated data.
 * @param p Pointer to the current node in the binary tree.
 */  
extern void
treeprint(struct tnode* p);

/*
 * Set -
 * */

/**
 * @brief This function inserts a node with the given key and data into the binary tree.
 * @param tree Pointer to the binary tree structure.
 * @param key Key of the node to be inserted.
 * @param data Data associated with the node to be inserted.
 * @return Returns an integer value indicating the success of the operation (always returns 1).
 */  
extern int
insert_node(struct binary_tree* tree, const char* key, void* data);


/**
 * @brief This function inserts a node with the given key and data into the binary tree.
 * @param root A pointer to the root node of the binary tree.
 * @param key The key associated with the node being inserted.
 * @param data The data associated with the node being inserted.
 * @return Returns a pointer to the root of the binary tree after inserting the new node.
 */  
extern struct tnode*
add_node(struct tnode* p, const char* key, void* data);

/**
 * @brief This function creates a new tree node with the given key and data.
 * @param key The key associated with the new tree node.
 * @param data The data associated with the new tree node.
 * @return Returnsa pointer to the newly created tree node.
    If the key is null or if memory allocation fails, it returns NULL.
 */  
extern struct tnode*
create_tnode(const char* key, void* data);

/*
 * Memory allocation -
 */


/**
 * @brief This function allocates memory for a new binary tree structure and initializes its root pointer to NULL.
 * @param btree A pointer to the binary tree structure being allocated.
 * @return Returns a a pointer to the newly allocated binary tree structure.
 */  
extern struct binary_tree*
btree_alloc(void);

/**
 * @brief This function creates a new binary tree
 * @return Returns a pointer to the newly created binary tree structure.
 */  
extern struct binary_tree*
create_new_btree(void);

/**
 * @brief This function frees the memory allocated for the binary tree.
 * @param btree A pointer to the binary tree structure that needs to be freed.
 */ 
extern void
btree_free(struct binary_tree* btree);

/**
 * @brief This function recursively frees the memory allocated for each node of the binary tree,
    including the associated data stored in the buckets.
 * @param root A pointer to the root node of the binary tree.
 */  
extern void
free_tree(struct tnode* p);

#endif /* _BINARY_TREE_H */
