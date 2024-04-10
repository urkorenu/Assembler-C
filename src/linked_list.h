#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "includes.h"

#define WORDSIZE 14
#define BITSIZE(x) (sizeof(x) * 8)
#define BITMASK(N) (1 << (N))
#define GET_BIT(X, N) (((X) & BITMASK(N)) >> (N))

enum node_state { DATA_UNSET, DATA_SET };

struct linked_list {
    int data;
    enum node_state state;
    struct linked_list* next;
    struct linked_list* pre;
};

#define get_lnode_data(lnode, dtype) ((dtype)((lnode)->data))

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
print_linked_list(const struct linked_list* p, FILE* file);

extern void
ll_fprintf(const struct linked_list* p, FILE* file, const char* sep);

extern void
llfree(struct linked_list* p);

#endif /* !LINKED_LIST_H */
