#include "linked_list.h"
#include <assert.h>

#define BITSIZE(x) (sizeof(x) * 8)
struct linked_list*
test_create(void);
void
test_set_data(struct linked_list* ll);
void
test_insert(struct linked_list* ll);
void
test_print(struct linked_list* ll);
void
test_free(struct linked_list* ll);

int
main(int argc, char** argv)
{

    struct linked_list* ll;
    ll = test_create();
    test_set_data(ll);
    test_insert(ll);
    test_print(ll);
    test_free(ll);
    return 0;
}

struct linked_list*
test_create(void)
{
    struct linked_list* ll = create_new_ll_node(0);
    assert(ll != NULL);
    assert(ll->data == 0);
    assert(ll->next == NULL);
    assert(ll->pre == NULL);
    assert(ll->state == DATA_UNSET);
    return ll;
}

void
test_set_data(struct linked_list* ll)
{
    int rnd = 1;
    set_data(ll, rnd);
    assert(ll->data == rnd);
}

void
test_insert(struct linked_list* ll)
{
    const int initial = ll->data;
    const int final = (initial + (1 << BITSIZE(char)) - 1);

    int i;

    for (i = initial + 1; i <= final; i++)
        insert_ll_node(ll, i);
    ll = get_last_node(ll);

    assert(ll);
    assert(ll->data == final);
    assert(ll->state == DATA_SET);
    assert(ll->next == NULL);
}

void
test_print(struct linked_list* ll)
{
    fprintf(stdout, "\n");
    ll_fprintf(ll, stdout, " <---> ");
    fprintf(stdout, "\n");
}

void
test_free(struct linked_list* ll)
{
    llfree(ll);
}
