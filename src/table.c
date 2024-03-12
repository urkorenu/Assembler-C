typedef struct label_address {
    int address;
    char *label_name;
    int line;
} label_address;


insert_label_table(label_address **label_table, int lines, char *label, int counter, int reading_symbol, source_file.line) {
    label_address *p_temp;

    p_temp = *label_table;

    /* Resize the label_table to accommodate the new entry */
    *label_table = realloc(*label_table, lines * sizeof(label_address));
    if (*label_table == NULL) {
        printf(ERROR);
        free(*p_temp);
        return 0;
    }

    /* Set the values for the new entry in the label_table */
    (*label_table + lines - 1)->reading_symbol = reading_symbol;
    (*label_table + lines - 1)->address = counter;
    (*label_table + lines - 1)->line= source_file.line;

    /* Allocate memory for the label_name and copy the label from the input */
    (*label_table + lines - 1)->label_name = malloc((strlen(label) + 1) * sizeof(char));
    if ((*label_table + lines - 1)->label_name == NULL) {
         printf(ERROR);
        return 0;
    }
    strcpy((*label_table + lines - 1)->label_name, label);

    /* Return 1 to indicate successful insertion */
    return 1;
}
