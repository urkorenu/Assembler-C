#ifndef ERROR_H
#define ERROR_H

#include "includes.h"

/* Simplifies error reporting by automatically passing error information to a
 * function for printing. */
#define print_in_error(code, line, word)                                       \
    _print_in_error((code), (line), __FILE__, __LINE__, (word));

/**
 * @brief This function prints an error message along with its code, originating
 file, and line number.
 * @param error_code The error code indicating the type of error.
 * @param line: The line number where the error occurred.
 * @param origin_file The file where the error originated.
 * @param origin_line The line number in the file where the error originated.
 * @param word The word that the errors accur.
 * @return Returns 1 if the instruction code and number of arguments were
 successfully assigned to the line_data structure, otherwise it returns 0.
 */
extern void
_print_in_error(int error_code,
                int line,
                char* origin_file,
                int origin_line,
                const char* word);

/**
 * @brief This function prints a file-related error message.
 * @param fp The filename causing the error.
 */
extern void
print_file_error(const char* fp);

/* Represents error enum for various types of errors */
typedef enum ERROR_CODES {
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
    KEY_DEFINED,
    MISSING_COMMAND,
    ILLEGAL_OPCODE,
    ILLEGAL_ARG,
    MISSING_ARG,
    MISSING_COMMA,
    EXTRA_COMMAS,
    MISPLACED_COMMA,
    ILLEGAL_REG,
    INVALID_COMMAND,
    NOT_DEFINED,
    TYPE_ERROR,
    MISSING_QUOTES,
    EXTRA_TEXT_AFTER_STRING,
    EXTERN_DEFINED,
    INVALID_DATA,
    ENTRY_IS_EXTERNAL,
    INVALID_DIRECT,
    ILLEGAL_CHAR,
    ILLEGAL_SYMBOL_NAME,

    TOTAL_NUMBER_OF_ERRORS
} ERROR_CODES;

#endif /* ERROR_H */
