#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "includes.h"

struct linked_list {
    void* data;
    struct linked_list* next;
    struct linked_list* pre;
};

extern struct linked_list*
create_new_ll_node(void* data);

extern void
insert_ll_node(struct linked_list* head, void* data);

extern struct linked_list*
get_last_node(struct linked_list* p);

extern struct linked_list*
llalloc(void);

#endif /* !LINKED_LIST_H */
