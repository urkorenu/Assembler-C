#include "files.h"

/* Error message for memory allocation failure */
const char FILES_ALLOC_ERR[] = {
    "Failed to allocate memory for struct files - Buy more RAM lol!\n"
};


/* Allocate memory for struct files */
extern struct files*
files_alloc(void)
{
    struct files* f = malloc(sizeof(struct files));
    if (f == NULL)
        fprintf(stderr, FILES_ALLOC_ERR);
    return f;
}

/* Free memory allocated for struct files */
extern void
files_free(struct files* f)
{
    free(f);
}

/* Modify file path by concatenating with a format */
char*
modify_path(const char* path, const char* format)
{
    char* new_path = malloc(strlen(path) + strlen(format) + 1);
    if (new_path == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    strcpy(new_path, path);
    strcat(new_path, format);

    return new_path;
}

/* Set file paths for a files structure */
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
