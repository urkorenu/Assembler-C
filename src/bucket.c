#include "bucket.h"

/*/////////////*/
/* Set methods */
/*/////////////*/

/* Set the key for a bucket.*/
static void
set_key(struct bucket* p, const char* key)
{
    p->key = mystrdup(key);
}

/* Set the data for a bucket.*/
static void
set_data(struct bucket* p, void* data)
{
    p->data = data;
}

/*//////////////////*/
/* Memory functions */
/*//////////////////*/

/* Allocate memory for a bucket. */
static struct bucket*
bucket_alloc(void)
{
    struct bucket *p = (struct bucket *)malloc(sizeof(struct bucket));
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
    set_key(p, key);
    set_data(p, data);
    return p;
}
