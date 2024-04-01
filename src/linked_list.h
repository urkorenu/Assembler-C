#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "includes.h"

struct linked_list {
    int data;
    struct linked_list* next;
    struct linked_list* pre;
};

#define get_lnode_data(lnode, dtype)\
    ((dtype)((lnode)->data))

extern struct linked_list*
create_new_ll_node(int data);

extern void
set_data(struct linked_list* p, int data);

extern struct linked_list*
insert_ll_node(struct linked_list* head, int data);

extern struct linked_list*
get_last_node(struct linked_list* p);

extern struct linked_list*
llalloc(void);

extern void 
print_linked_list(struct linked_list *p, FILE *file);

#endif /* !LINKED_LIST_H */
