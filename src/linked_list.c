/*
 * File: linked_list.c
 * Description: This file contains the core and methods of the linked list data
 * structure.
 */

#include "linked_list.h"
#include "bucket.h"
#include <stdio.h>

/* Function prototypes */
static void
_print_linked_list(const struct linked_list* p, FILE* file, const char* sep);
static void
int_to_binary(int n, FILE* file);
static void
encrypt_binary(int n, FILE* file);

/* Set data and state for the node */
void
set_data(struct linked_list* p, void* data)
{
    p->data = data;
    p->state = DATA_SET;
}

void
set_data_int(struct linked_list* p, int data)
{
    int* iptr;
    iptr = malloc(sizeof(int));
    iptr[0] = data;
    p->data = iptr;
    p->state = DATA_SET;
}

/* Allocate memory for a new linked list node */
struct linked_list*
create_new_ll_node(void* data)
{
    struct linked_list* new_node;
    new_node = (struct linked_list*)malloc(sizeof(struct linked_list));
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

/* Insert a new node at the end of the linked list */
struct linked_list*
insert_ll_node(struct linked_list* head, void* data)
{
    struct linked_list* last_node;

    if (head == NULL)
        last_node = head = create_new_ll_node(data);
    else
        last_node = get_last_node(head);

    last_node = last_node->next = create_new_ll_node(data);

    set_data(last_node, data);
    if (data == 0)
        last_node->state = DATA_UNSET;
    return last_node;
}

struct linked_list*
get_last_unset_node(struct linked_list* p, int* ic)
{
    while (p->next != NULL) {
        if (p->next->state == DATA_UNSET) {
            (*ic)++;
            return p->next;
        }
        p = p->next;
        (*ic)++;
    }
    return p;
}

/* Get the last node of the linked list */
struct linked_list*
get_last_node(struct linked_list* p)
{
    while (p->next != NULL)
        p = p->next;
    return p;
}

/* Free memory allocated for the linked list */
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

/* Print the linked list to a file */
void
print_linked_list(const struct linked_list* p, FILE* file)
{
    ll_fprintf(p, file, "\n");
}

/* Print the linked list to a file with a custom separator */
void
ll_fprintf(const struct linked_list* p, FILE* file, const char* sep)
{
    if (file == NULL) {
        fprintf(stderr, "Error: Invalid file pointer.\n");
    } else if (p != NULL) {
        _print_linked_list(p, file, ((sep == NULL) ? "\n" : sep));
    }
}

/* Helper function to recursively print the linked list */
static void
_print_linked_list(const struct linked_list* p, FILE* file, const char* sep)
{
    if (p->state == DATA_SET) {
        if (p->data)
            encrypt_binary(((int*)p->data)[0], file);
            /*int_to_binary(((int*)p->data)[0], file);*/
        if (p->data == 0)
            encrypt_binary(0, file);
    }
    if (p->next != NULL) {
        fprintf(file, "%s", sep);
        _print_linked_list(p->next, file, sep);
    }
}

void
print_e_list(const struct linked_list* p, FILE* file, const char* sep)
{
    struct bucket* b;
    if (p != NULL) {
        if (p->data != NULL) {
            b = p->data;
            fprintf(file, "%s ", b->key);
            fprintf(file, "0%-4d", ((int*)b->data)[0]);
        }
    }
    if (p->next != NULL) {
        fprintf(file, "%s", sep);
        print_e_list(p->next, file, sep);
    }
}

/* Helper function to convert an integer to binary and print to file */
static void
int_to_binary(int n, FILE* file)
{
    int i;
    if (n == 0) {
        fprintf(file, "?");
        return;
    }
    for (i = WORDSIZE - 1; i >= 0; i--)
        fprintf(file, "%0d", GET_BIT(n, i));
}

/* Helper function to encrypt binary representation and print to file */
static void
encrypt_binary(int n, FILE* file)
{
    int bit_sum, first_bit, i;
    for (i = WORDSIZE - 1; i >= 0; i -= 2) {
        first_bit = GET_BIT(n, i) * 2;
        bit_sum = first_bit + GET_BIT(n, i - 1);
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
