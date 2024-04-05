#include "linked_list.h"

#define WORDSIZE 14
#define BITSIZE(x) (sizeof(x) * 8)
#define BITMASK(N) (1 << (N))
#define GET_BIT(X, N) (((X) & BITMASK(N)) >> (N))

static void
_print_linked_list(const struct linked_list* p, FILE* file, const char* sep);

void
set_data(struct linked_list* p, int data)
{
    p->data = data;
    p->state = DATA_SET;
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
    new_node->data = 0;
    new_node->next = NULL;
    new_node->pre = NULL;
    new_node->state = DATA_UNSET;
    return new_node;
}

struct linked_list*
insert_ll_node(struct linked_list* head, int data)
{
    struct linked_list* last_node;

    if (head == NULL)
        last_node = head = create_new_ll_node(data);
    else
        last_node = get_last_node(head);

    if (last_node->state == DATA_SET)
        last_node = last_node->next = create_new_ll_node(data);

    set_data(last_node, data);
    return last_node;
}

struct linked_list*
get_last_node(struct linked_list* p)
{
    if (p->state == DATA_UNSET || p->next == NULL)
        return p;
    return get_last_node(p->next);
}

struct linked_list*
llalloc(void)
{
    return (struct linked_list*)malloc(sizeof(struct linked_list));
}

void
llfree(struct linked_list* p)
{
    if (p == NULL) {
        return;
    }
    if (p->next != NULL) {
        llfree(p->next);
    }
    p->next = NULL;
    p->pre = NULL;
    free(p);
}

static void
int_to_binary(int n, FILE* file)
{
    if (n == 0) {
        fprintf(file, "?");
        return;
    }
    for (int i = WORDSIZE - 1; i >= 0; i--)
        fprintf(file, "%0d", GET_BIT(n, i));
}

static void
encrypt_binary(int n, FILE *file)
{
    int bit_sum, first_bit;
    for (int i = WORDSIZE - 1; i >= 0; i-=2)
    {
        first_bit = GET_BIT(n, i) * 2;
        bit_sum = first_bit + GET_BIT(n, i-1);
        if (!bit_sum)
            fprintf(file, "%c", '*');
        else if (bit_sum == 1)
            fprintf(file, "%c", '#');
        else if (bit_sum == 2)
            fprintf(file, "%c", '%');
        else 
            fprintf(file, "%c", '!');

    }
}

void
print_linked_list(const struct linked_list* p, FILE* file)
{
    ll_fprintf(p, file, "\n");
}

void
ll_fprintf(const struct linked_list* p, FILE* file, const char* sep)
{
    if (file == NULL) {
        fprintf(stderr, "Error: Invalid file pointer.\n");
    } else if (p != NULL) {
        _print_linked_list(p, file, ((sep == NULL) ? "\n" : sep));
    }
}

static void
_print_linked_list(const struct linked_list* p, FILE* file, const char* sep)
{
    if (p->state == DATA_SET) {
        /*encrypt_binary(get_lnode_data(p, int), file);*/
        int_to_binary(get_lnode_data(p, int), file);
    }
    if (p->next != NULL) {
        fprintf(file, "%s", sep);
        _print_linked_list(p->next, file, sep);
    }
}
