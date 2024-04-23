#include "bucket.h"
#include "io.h"

/*/////////////*/
/* Set methods */
/*/////////////*/

/* Set the key for a bucket.*/
void
bucket_set_key(struct bucket* p, const char* key)
{
    p->key = mystrdup(key);
}

/* Set the data for a bucket.*/
void
bucket_set_data(struct bucket* p, void* data)
{
    p->data = data;
}

void set_bucket_ic(struct bucket* b, int ic)
{
    int* iptr;
    if (!b && !ic)
        return;

    iptr = int_to_voidp(ic);
    b->data = iptr;
}


/*//////////////////*/
/* Memory functions */
/*//////////////////*/

/* Allocate memory for a bucket. */
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

/* Free the memory of a bucker*/
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

/* Reset a bucket by zeroing out its memory. */
void
reset_bucket(struct bucket* p)
{
    memset(p, 0, sizeof(struct bucket));
}

/* Reset a bucket by zeroing out its memory. */
struct bucket*
create_bucket(const char* key, void* data)
{
    struct bucket* p = bucket_alloc();
    bucket_set_key(p, key);
    bucket_set_data(p, data);
    return p;
}
