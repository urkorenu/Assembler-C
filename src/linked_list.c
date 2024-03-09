#include "linked_list.h"

struct linked_list *create_new_ll_node(void *data) {
  struct linked_list *new_node;
  new_node = llalloc();
  if (new_node == NULL) {
    printf("Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

void insert_ll_node(struct linked_list *head, void *data) {
    if (!head || !data)
        return;
    struct linked_list *last_node = get_last_node(head);
    last_node->next = create_new_ll_node(data);
}

struct linked_list *get_last_node(struct linked_list *p) {
    if (p->next == NULL)
        return p;
    return get_last_node(p->next);
}

struct linked_list *llalloc(void) {
    return (struct linked_list *)malloc(sizeof(struct linked_list));
}
