#include "include/bucket.h"
#include "include/io.h"

void
bucket_set_key(struct bucket* p, const char* key)
{
    p->key = str_dup(key);
}

void
bucket_set_data(struct bucket* p, void* data)
{
    p->data = data;
}

void
set_bucket_ic(struct bucket* b, int ic)
{
    int* iptr;

    if (!b && !ic)
        return;

    iptr = int_to_voidp(ic);
    b->data = iptr;
}

struct bucket*
bucket_alloc(void)
{
    struct bucket* p = (struct bucket*)malloc(sizeof(struct bucket));

    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed for bucket\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

void
free_bucket(struct bucket* p)
{
    if (p == NULL)
        return;

    free(p->key);
    free(p->data);
    free(p);
    p = NULL;
}

void
reset_bucket(struct bucket* p)
{
    memset(p, 0, sizeof(struct bucket));
}

struct bucket*
create_bucket(const char* key, void* data)
{
    struct bucket* p = bucket_alloc();

    bucket_set_key(p, key);
    bucket_set_data(p, data);
    return p;
}
