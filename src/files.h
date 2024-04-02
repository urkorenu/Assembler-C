#ifndef _FILES_H
#define _FILES_H

#include "includes.h"

#define ASSEMBLY ".as"
#define PROCESSED ".am"
#define OBJECT ".ob"
#define EXTERN ".ext"
#define ENTRY ".ent"

struct files {
    char* assembly_path;
    char* processed_path;
    char* object_path;
    char* entries_path;
    char* externals_path;
};

extern const char FILES_ALLOC_ERR[];

extern const struct files DEFAULT_FILES_VAL;

extern struct files*
files_alloc(void);

extern void
files_free(struct files* f);

extern char*
modify_path(const char* path, const char* format);

extern void
set_file_pack(struct files* files, const char* path);

#endif /*_FILES_H*/
