#include "include/files.h"
#include "include/error.h"
#include "include/io.h"

extern struct files*
files_alloc(void)
{
    struct files* f = malloc(sizeof(struct files));
    if (f == NULL)
        fprintf(stderr, FILES_ALLOC_ERR);
    return f;
}

extern void
files_free(struct files* f)
{
    free(f->object_path);
    free(f->entries_path);
    free(f->assembly_path);
    free(f->externals_path);
    free(f->processed_path);
    free(f);
}

char*
modify_path(const char* path, const char* format)
{
    char* new_path = malloc(strlen(path) + strlen(format) + 1);
    if (new_path == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    if (!path)
        return NULL;
    strcpy(new_path, path);
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

int
try_init_files(struct files paths, FILE** fread, FILE** fwrite)
{
    if (!fread || !fwrite)
        return 0;

    *fread = verbose_fopen(paths.assembly_path, "r");

    if ((*fread) != NULL) {
        *fwrite = verbose_fopen(paths.processed_path, "w");

        if ((*fwrite) == NULL)
            print_in_error(FAILED_OPEN_WRITING, 0, NULL);
    } else {
        print_in_error(FAILED_OPEN_READING, 0, NULL);
    }
    return (fread[0] != NULL && fwrite[0] != NULL);
}
