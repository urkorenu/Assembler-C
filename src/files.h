#ifndef _FILES_H
#define _FILES_H

#include "includes.h"

/*Definition of the file name extension*/
#define ASSEMBLY ".as"
#define PROCESSED ".am"
#define OBJECT ".ob"
#define EXTERN ".ext"
#define ENTRY ".ent"

struct files {
    char* assembly_path; /*A pointer to a string representing  the path of the source file.*/
    char* processed_path;/* A pointer to a string representing the path for the processed file.*/
    char* object_path; /*A pointer to a string representing the path for the object file.*/
    char* entries_path; /*A pointer to a string representing the path for the entries file.*/
    char* externals_path; /*A pointer to a string representing the path for the externals file.*/
};

extern const char FILES_ALLOC_ERR[];

extern const struct files DEFAULT_FILES_VAL;

/**
 * @brief This function  Allocate memory for struct files.
 * @param f is a pointer to a struct files
 * @return Returns a pointer to the allocated memory if memory allocation is successful,
    otherwise, it prints an error message and returns NULL.
 */ 
extern struct files*
files_alloc(void);

/**
 * @brief This function free memory allocated for struct files.
 * @param f is a pointer to a struct files
 */ 
extern void
files_free(struct files* f);

/**
 * @brief This function concatenates a file path with a format string to create a new path.
 * @param path A pointer to a string representing the original file path.
 * @param format A pointer to a string representing the format to append to the original path.
 * @return Returns  a pointer to a newly allocated string representing the concatenated path,
   or NULL if memory allocation fails.
 */ 
extern char*
modify_path(const char* path, const char* format);

/**
 * @brief This function sets file paths for various types of files within a files structure.
 * @param files A pointer to a files structure where the file paths will be set.
 * @param path A pointer to a string representing the base path used to construct other file paths.
 */ 
extern void
set_file_pack(struct files* files, const char* path);

extern int
try_init_files(struct files paths, FILE** fread, FILE** fwrite);

#endif /*_FILES_H*/
