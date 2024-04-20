#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "assembler.h"
#include "includes.h"

#define WORDSIZE 14
#define BITSIZE(x) (sizeof(x) * 8)
#define BITMASK(N) (1 << (N))
#define GET_BIT(X, N) (((X) & BITMASK(N)) >> (N))

enum node_state { DATA_UNSET, DATA_SET };

struct linked_list {
    void* data;
    enum node_state state;
    struct linked_list* next;
    struct linked_list* pre;
};

#define get_lnode_data(lnode, dtype) ((dtype)((lnode)->data))

extern struct linked_list*
create_new_ll_node(void* data);

 /**
 * @brief This function sets the data pointer of a linked list node to a specified value and updates its state to indicate that the data has been set.
 * @param  p A pointer to the linked list node whose data will be set.
 * @param data The data value to be assigned to the linked list node.
 */ 
extern void
set_data(struct linked_list* p, void* data);

 /**
 * @brief This function sets the data of a linked list node to an integer value
 * @param p A pointer to the linked list node whose data will be set.
 * @param data The integer value to be assigned to the linked list node.
 */ 
extern void
set_data_int(struct linked_list* p, int data);

/**
 * @brief This function allocates memory for a new linked list node.
 * @param new_node A pointer to the newly created linked list node.
 * @param data The data to be stored in the new linked list node.
 * @return Returns a pointer to the newly created linked list node.
 */ 
extern struct linked_list*
insert_ll_node(struct linked_list* head, void* data);

extern struct linked_list*
get_first_unset_node(struct linked_list* p, int* ic);

extern struct linked_list*
get_last_node(struct linked_list* p);

extern struct linked_list*
llalloc(void);

extern void
print_linked_list(struct assembler_data* assembler);

extern void
print_e_list(const struct linked_list* p, FILE* file, const char* sep);

extern void
llfree(struct linked_list* p);

#endif /* !LINKED_LIST_H */
