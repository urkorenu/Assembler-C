#include "files.h"

char *modify_path(const char *path, const char *format) {

    char *new_path = malloc(strlen(path) + 1); 
    if (new_path == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    strcat(new_path, path);
    strcat(new_path, format);

    return new_path;
}


void set_file_pack(struct files *files, const char *path)
{
    files->assembly_path = modify_path(path, ASSEMBLY);
    files->processed_path = modify_path(path, PROCESSED);
    files->object_path = modify_path(path, OBJECT);
    files->externals_path = modify_path(path, EXTERN);
    files->entries_path = modify_path(path, ENTRY);
    return;
}

