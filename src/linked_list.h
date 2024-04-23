#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "assembler.h"
#include "includes.h"

#define WORDSIZE 14 /* Defines the size of a word */
#define BITSIZE(x) (sizeof(x) * 8) /* Calculates the size of a variable x in bits. */
#define BITMASK(N) (1 << (N)) /* Generates a bitmask for a specific bit position N. */
#define GET_BIT(X, N) (((X) & BITMASK(N)) >> (N)) /* Retrieves the value of a specific bit N from an integer X. */

 /* Represents the state of a node in a linked list. */
enum node_state { DATA_UNSET, DATA_SET };

struct linked_list {
    void* data; /* Stores the data associated with the current node in the linked list. */
    enum node_state state; /* The state of the current node in the linked list. */
    struct linked_list* next; /* A pointer to the next node in the linked list. */
    struct linked_list* pre; /* a pointer to the previous node in the linked list. */
};

#define get_lnode_data(lnode, dtype) ((dtype)((lnode)->data))
/**
 * @brief This function allocates memory for a new linked list node.
 * @param new_node A pointer to the newly created linked list node.
 * @param data The data to be stored in the new linked list node.
 * @return Returns a pointer to the newly created linked list node.
 */ 
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
 * @brief This function inserts a new node containing the provided data at the end of the linked list.
 * @param  head A pointer to the head of the linked list.
 * @param  last_node A pointer to the last node of the linked list.
 * @return Returns a pointer to the newly inserted node at the end of the linked list.
 */ 
extern struct linked_list*
insert_ll_node(struct linked_list* head, void* data);


 /**
 * @brief This function traverses the linked list starting from the provided node p
   and returns the first node with its data state unset.
 * @param p A pointer to the current node from which the traversal begins.
 * @param ic A pointer to the instruction counter, which is incremented for each node visited.
 * @return Returns  a pointer to the first node with its data state unset in the linked list.
 */ 
extern struct linked_list*
get_first_unset_node(struct linked_list* p, int* ic);

 /**
 * @brief This function gets the last node of the linked list.
 * @param p A pointer to the current node from which the traversal begins.
 * @return Returns a pointer to the last node in the linked list.
 */ 
extern struct linked_list*
get_last_node(struct linked_list* p);

extern struct linked_list*
llalloc(void);

 /**
 * @brief This function prints the contents of the object list linked list to a file.
 * @param assembler A pointer to the assembler data structure containing information about the assembly process.
 * @param file A file pointer used to write to the file.
 */ 
extern void
print_linked_list(struct assembler_data* assembler);

/**
 * @brief This function print the elements of a linked list to a file. 
 * @param  p Pointer to the current node of the linked list.
 * @param file File pointer representing the file where the elements will be printed.
 * @param sep Separator string used to separate elements in the file.
 */ 
extern void
print_e_list(const struct linked_list* p, FILE* file, const char* sep);


 /**
 * @brief This function recursively frees the memory allocated for each node in the linked list
 * @param p A pointer to the current node from which the traversal begins.
 */ 
extern void
llfree(struct linked_list* p, int free_b);

#endif /* !LINKED_LIST_H */
