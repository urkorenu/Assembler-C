/*
 * File: linked_list.c
 * Description: This file contains the core and methods of the linked list data
 * structure.
 */

#include "include/linked_list.h"
#include "include/assembler.h"
#include "include/bucket.h"
#include "include/files.h"
#include "include/io.h"

/* Function prototypes */
/**
 * @brief This function prints the contents of a linked list to a file
 * @param p A pointer to the linked list structure containing the data to be
 * printed.
 * @param file A pointer to the file where the contents will be printed.
 * @param sep The separator string used to separate each element in the output.
 * @param ic The instruction counter value appended to each element in the
 * output.
 */
static void
_print_linked_list(const struct linked_list* p,
                   FILE* file,
                   const char* sep,
                   int ic);
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
    p->data = int_to_voidp(data);
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
get_first_unset_node(struct linked_list* p, int* ic)
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
llfree(struct linked_list* p, int free_b)
{
    if (p == NULL) {
        return;
    }
    if (p->next != NULL) {
        llfree(p->next, free_b);
    }
    p->next = NULL;
    p->pre = NULL;
    if (free_b)
        free_bucket(p->data);
    else {
        free(p->data);
    }
    free(p);
    p = NULL;
}

/* Print the linked list to a file with a custom separator */
void
ll_fprintf(const struct linked_list* p,
           FILE* file,
           const char* sep,
           int ic,
           struct assembler_data* assembler)
{
    if (file == NULL) {
        fprintf(stderr, "Error: Invalid file pointer.\n");
    } else if (p != NULL) {
        fprintf(file, "   %d %d", assembler->instruction_c, assembler->data_c);
        _print_linked_list(p, file, ((sep == NULL) ? "\n" : sep), ic);
    }
}

/* Print the linked list to a file */
void
print_linked_list(struct assembler_data* assembler)
{
    FILE* file = fopen(assembler->as_files->object_path, "w");
    ll_fprintf(assembler->object_list, file, "\n", 100, assembler);
}

/* Helper function to recursively print the linked list */
static void
_print_linked_list(const struct linked_list* p,
                   FILE* file,
                   const char* sep,
                   int ic)
{
    if (p->state == DATA_SET) {
        fprintf(file, "0%d  ", ic++);
        if (p->data)
            encrypt_binary(((int*)p->data)[0], file);
        if (p->data == 0)
            encrypt_binary(0, file);
    }
    if (p->next != NULL) {
        fprintf(file, "%s", sep);
        _print_linked_list(p->next, file, sep, ic);
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
