#include "linked_list.h"

struct linked_list*
create_new_ll_node(void* data)
{
    struct linked_list* new_node;
    new_node = llalloc();
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

struct linked_list*
insert_ll_node(struct linked_list* head, void* data)
{
    if (!data)
        return NULL;
    if (head->data == NULL) {
        head = create_new_ll_node(data);
        return head;
    }
    struct linked_list* last_node = get_last_node(head);
    last_node->next = create_new_ll_node(data);
    return last_node->next;
}

struct linked_list*
get_last_node(struct linked_list* p)
{
    if (p->next == NULL)
        return p;
    return get_last_node(p->next);
}

struct linked_list*
llalloc(void)
{
    return (struct linked_list*)malloc(sizeof(struct linked_list));
}

void print_linked_list(struct linked_list *p, FILE *file) {
    if (file == NULL) {
        printf("Error: Invalid file pointer.\n");
        return;
    }

    if (!p || !p->data) 
        return;
    fprintf(file, "%d\n", get_lnode_data(p, int));
    print_linked_list(p->next, file);
}

