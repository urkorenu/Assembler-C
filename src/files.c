#include "files.h"

const char FILES_ALLOC_ERR[] = {
    "Failed to allocate memory for struct files - Buy more ram lol!\n"
};

const struct files DEFAULT_FILES_VAL = {
    .assembly_path=ASSEMBLY,
    .processed_path=PROCESSED,
    .object_path=OBJECT,
    .externals_path=EXTERN,
    .entries_path=ENTRY,
};


extern struct files*
files_alloc(void)
{
    struct files* f = malloc(sizeof(struct files));
    if (f != NULL)
        f[0] = (DEFAULT_FILES_VAL);
    else
        fprintf(stderr, FILES_ALLOC_ERR);
    return f;
}

extern void
files_free(struct files* f)
{
    free(f);
}


char*
modify_path(const char* path, const char* format)
{

    char* new_path = malloc(strlen(path) + 1);
    if (new_path == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    strcat(new_path, path);
    strcat(new_path, format);

    return new_path;
}

void
set_file_pack(struct files* files, const char* path)
{
    files->assembly_path = modify_path(path, ASSEMBLY);
    files->processed_path = modify_path(path, PROCESSED);
    files->object_path = modify_path(path, OBJECT);
    files->externals_path = modify_path(path, EXTERN);
    files->entries_path = modify_path(path, ENTRY);
    return;
}
