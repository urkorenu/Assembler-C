#include "linked_list.h"

void
set_data(struct linked_list* p, int data)
{
    p->data = data;
}
struct linked_list*
create_new_ll_node(int data)
{
    struct linked_list* new_node;
    new_node = llalloc();
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    set_data(new_node, data);
    new_node->next = NULL;
    return new_node;
}

struct linked_list*
insert_ll_node(struct linked_list* head, int data)
{
    if (head == NULL) {
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

static void
int_to_binary(int n)
{
    int i, a[15];
    for (i = 0; n > 0; i++) {
        a[i] = n % 2;
        n = n / 2;
    }
    for (i = i - 1; i >= 0; i--) {
        printf("%d", a[i]);
    }
    printf("\n");
}

void
print_linked_list(struct linked_list* p, FILE* file)
{
    if (file == NULL) {
        printf("Error: Invalid file pointer.\n");
        return;
    }

    if (!p)
        return;
    /*fprintf(file, "%d\n", get_lnode_data(p, int));*/
    int_to_binary(get_lnode_data(p, int));
    print_linked_list(p->next, file);
}
