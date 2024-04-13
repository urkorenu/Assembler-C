#ifndef _BUCKET_H
#define _BUCKET_H

#include "includes.h"
#include "io.h"

#define _b_get_data(bucket, dtype) ((dtype*)((bucket)->data))

#define b_get_data(bucket, dtype)                                              \
    (_b_get_data(bucket, dtype) != NULL ? _b_get_data(bucket, dtype)[0] : NULL)

#define b_set_data(bucket, data_, dtype)                                       \
    do {                                                                       \
        if ((bucket)->data == NULL)                                            \
            (bucket)->data = malloc(sizeof(dtype));                            \
        ((dtype*)((bucket)->data))[0] = (data_);                               \
    } while (0)

struct bucket {
    char* key;
    void* data;
};

typedef void (*free_fn)(void* data);

extern struct bucket*
bucket_alloc(void);

extern struct bucket*
create_bucket(const char* key, void* data);

extern void
bucket_set_key(struct bucket* p, const char* key);

extern void
bucket_set_data(struct bucket* p, void* data);

extern void
set_bucket_ic(struct bucket* b, int ic);

extern void
free_bucket(struct bucket* p);

extern void
reset_bucket(struct bucket* p);

#endif /* _BUCKET_H */
