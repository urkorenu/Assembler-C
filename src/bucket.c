#include "bucket.h"

static void
set_key(struct bucket* p, char* key)
{
    p->key = mystrdup(key);
}

static void
set_data(struct bucket* p, void* data)
{
    p->data = data;
}

static struct bucket*
bucket_alloc(void);

struct bucket*
create_bucket(char* key, void* data)
{
    struct bucket* p;
    p = bucket_alloc();
    set_key(p, key);
    set_data(p, data);
    printf("%s", (char *)data);
    return p;
}

static struct bucket*
bucket_alloc(void)
{
    return (struct bucket*)malloc(sizeof(struct bucket));
}

void
free_bucket(struct bucket* p)
{
    free(p->key);
    free(p->data);
    free(p);
}

void
reset_bucket(struct bucket* p)
{
    memset(p, 0, sizeof(struct bucket));
}

char*
mystrdup(char* s)
{
    char* p;

    p = (char*)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);

    return p;
}
