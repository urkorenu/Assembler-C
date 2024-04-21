#ifndef ERROR_H
#define ERROR_H

#include "includes.h"

/* Simplifies error reporting by automatically passing error information to a function for printing. */
#define print_in_error(code, line) _print_in_error((code), (line), __FILE__, __LINE__);

/* this func print internal errors. */
extern void
_print_in_error(int error_code, int line, char* origin_file, int origin_line);

/**
 * @brief This function prints a file-related error message.
 * @param fp The filename causing the error.
 */  
extern void
print_file_error(const char *fp);

/* Represents error codes for various types of errors */
typedef enum ERROR_CODES {
    /* The following errors are macro related or general */
    VALID = 0,
    DYNAMIC_ALLOCATE_FAIL,
    FILENAME_TOO_LONG,
    FILE_NAME_DOESNT_EXIST,
    LINE_TOO_LONG,
    FAILED_OPEN_WRITING,
    FAILED_OPEN_READING,
    MACRO_DOESNT_END,
    EXTRA_TEXT,
    SYMBOL_DEFINED,
    MACRO_DEFINED,
    NO_MACRO,
    ILLEGAL_NAME,
    SYMBOL_NOT_FOUND,

    /* The following errors are related to reading command assembly lines */
    KEY_DEFINED,
    MISSING_COMMAND,
    ILLEGAL_OPCODE,
    ILLEGAL_ARG,
    MISSING_ARG,
    MISSING_COMMA,
    EXTRA_COMMAS,
    MISPLACED_COMMA,
    ILLEGAL_REG,
    INVALID_COMMAD,
    NOT_DEFINED,

    /* The following errors are related to reading instruction .data or .string
       lines related errors */
    TYPE_ERROR,
    MISSING_QUOTES,
    EXTRA_TEXT_AFTER_STRING,
    EXTERN_DEFINED,
    INVAILD_DATA,

    TOTAL_NUMBER_OF_ERRORS
} ERROR_CODES;


#endif /* ERROR_H */
