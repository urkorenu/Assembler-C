#include "bucket.h"

static struct bucket *bucket_alloc(void);

struct bucket *create_bucket(struct bucket *p, char *key, void *data)
{
    p = bucket_alloc();
    p->key = mystrdup(key);
    p->data = data;
    return p;
}

static struct bucket *bucket_alloc(void)
{
    return (struct bucket *)malloc(sizeof(struct bucket));
}

void free_bucket(struct bucket *p)
{
    free(p->key);
    free(p->data);
    free(p);
}

void reset_bucket(struct bucket *p)
{
    memset(p, 0, sizeof(struct bucket));
}

char *mystrdup(char *s)
{
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p,s);

    return p;
}
