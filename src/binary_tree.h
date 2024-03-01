#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "includes.h"
#include "bucket.h"

/* 
 * General Binary Tree -
 *      
 *  Structs
 *  */

struct tnode {
    struct bucket *node;
    struct tnode *left_node;
    struct tnode *right_node;
};

struct binary_tree{
        struct tnode *root;
};


/*
 * Methods 
 *
 *  Get - 
 * */



extern struct tnode *find_node(struct binary_tree *tree, char *key);

extern void *get_data_by_key(struct binary_tree *tree, char *key);

/* 
 * Set -
 * */

extern int insert_node(struct binary_tree *tree, char *key, void *data);

extern struct tnode *add_node(struct tnode *p, char *key, void *data);

extern int remove_node(struct binary_tree *tree, char *key);

extern struct tnode *create_tnode(struct tnode *p, char *key, void *data);

/* 
 * Memory allocation -
 */

extern void free_tree(struct tnode *p);

#endif /* _BINARY_TREE_H */

