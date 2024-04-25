#include "include/error.h"

static char errors[TOTAL_NUMBER_OF_ERRORS][100] = { { 0 } };

static void
init_errors(void);

void
print_file_error(const char* fp)
{
    if (!errno)
        return;
    fprintf(stderr, "Fatal Error:\n%*s\"%s\": ", 4, " ", fp);
    perror("");
}

void
_print_in_error(int error_code,
                int line,
                char* origin_file,
                int origin_line,
                const char* word)
{
    if (!errors[0][0])
        init_errors();
    printf("[Error] %s(%d): ", origin_file, origin_line);
    if (word)
        printf("\"%s\" ", word);
    printf("%s ", errors[error_code]);
    if (line > 0) {
        printf("in Line: %d \n", line);
    } else {
        printf("\n");
    }
}

static void
init_errors(void)
{
    strcpy(errors[VALID], "No Error");
    strcpy(errors[FILENAME_TOO_LONG], "The file name is too long");
    strcpy(errors[FILE_NAME_DOESNT_EXIST],
           "The provided file name does not exist");
    strcpy(errors[LINE_TOO_LONG], "The Line is too long");
    strcpy(errors[FAILED_OPEN_WRITING], "Failed to open new file for writing");
    strcpy(errors[FAILED_OPEN_READING], "Failed to open file for reading");
    strcpy(errors[EXTRA_TEXT], "Extra text");
    strcpy(errors[SYMBOL_DEFINED], "Symbol has more than one definition");
    strcpy(errors[MACRO_DEFINED], "Macro has more than one definition");
    strcpy(errors[NO_MACRO], "Macro call before declaration");
    strcpy(errors[ILLEGAL_NAME], "Illegal name");
    strcpy(errors[SYMBOL_NOT_FOUND], "The symbol is not found in the table");
    strcpy(errors[KEY_DEFINED], "define key is already initialized");
    strcpy(errors[MISSING_COMMAND], "Missing command");
    strcpy(errors[ILLEGAL_OPCODE], "Illegal opcode");
    strcpy(errors[ILLEGAL_ARG], "Illegal argument");
    strcpy(errors[MISSING_ARG], "Missing argument");
    strcpy(
      errors[MISSING_COMMA],
      "Missing comma between argument in a command line with two arguments");
    strcpy(errors[EXTRA_COMMAS], "More commas than needed");
    strcpy(errors[MISPLACED_COMMA], "Comma in the wrong place");
    strcpy(errors[ILLEGAL_REG], "Illegal register name. Use only r1-r7");
    strcpy(errors[TYPE_ERROR],
           "Instruction '.data' line contains non-number info");
    strcpy(errors[MISSING_QUOTES], "Missing '\"' after '.string'");
    strcpy(errors[EXTRA_TEXT_AFTER_STRING],
           "Extra text after the string end in '.string' line");
    strcpy(errors[EXTERN_DEFINED],
           "Label defined as .extern and defined in file");
    strcpy(errors[INVALID_DATA], "Input number in .data line is out of range");
    strcpy(errors[ENTRY_IS_EXTERNAL], "Entry is equals to external");
    strcpy(errors[INVALID_COMMAND], "Invalid command");
    strcpy(errors[INVALID_DIRECT], "Direct arg is empty");
    strcpy(errors[ILLEGAL_CHAR], "is not a legal char");
    strcpy(errors[ILLEGAL_SYMBOL_NAME], "is not legal symbol name");
    strcpy(errors[NOT_DEFINED],
           "The data you are looking for has not been defined");
}
