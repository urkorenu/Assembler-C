#ifndef _BUCKET_H
#define _BUCKET_H

struct bucket{
    char *key;
    void *data;
}; 

typedef void (*free_fn)(void *data);

extern void remove_bucket(char *key, free_fn free_data);

#endif /* _BUCKER_H */
