#ifndef _BUCKET_H
#define _BUCKET_H

#include "includes.h"

struct bucket {
    char* key;
    void* data;
};

typedef void (*free_fn)(void* data);

extern struct bucket*
create_bucket(const char* key, void* data);

extern void
free_bucket(struct bucket* p);

extern void
reset_bucket(struct bucket* p);

#endif /* _BUCKET_H */
