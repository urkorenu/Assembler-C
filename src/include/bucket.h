#ifndef _BUCKET_H
#define _BUCKET_H

#include "includes.h"

struct bucket {
    char* key;  /*represents the key - a string */
    void* data; /*represents the value of the variable*/
};

/*function declaration for allocating memory dynamically to a struct bucket
 * object and returning a pointer to it.*/
extern struct bucket*
bucket_alloc(void);

/**
 * @brief This function creates a new struct bucket instance, initializes it
 * with the provided key and data.
 * @param key Represents the key associated with the bucket.
 * @param data A pointer to the data stored in the bucket.
 * @return Returns a pointer to the created bucket.
 */
extern struct bucket*
create_bucket(const char* key, void* data);

/**
 * @brief This function sets the key for a bucket.
 * @param p A pointer to the bucket whose key is to be set.
 * @param key A constant character pointer representing the key to be assigned
 * to the bucket.
 */
extern void
bucket_set_key(struct bucket* p, const char* key);

/**
 * @brief This function sets the data for a bucket.
 * @param p A pointer to the bucket whose data is being set.
 * @param data The data that will be stored in the bucket.
 */
extern void
bucket_set_data(struct bucket* p, void* data);

/**
 * @brief This function sets the instruction counter (ic) in a bucket.
 * @param b A pointer to the bucket whose instruction counter will be set.
 * @param ic The value of the instruction counter to be set in the bucket.
 */
extern void
set_bucket_ic(struct bucket* b, int ic);

/**
 * @brief This function frees the memory allocated for a bucket.
 * @param p A pointer to the bucket whose memory will be freed.
 */
extern void
free_bucket(struct bucket* p);

/**
 * @brief This function reset a bucket by zeroing out its memory.
 * @param p A pointer to the bucket whose needs to be reset.
 */
extern void
reset_bucket(struct bucket* p);

#endif /* _BUCKET_H */
