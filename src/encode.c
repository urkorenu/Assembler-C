#include "encode.h"

void
encode_register(struct assembler_data* assembler,
                struct line_data* inst,
                int found_register,
                struct linked_list* source_code,
                int source)
{
    int bit_location = DESTINATION_REGISTER;
    int operand_location = DESTINATION_OPERAND;
    int code;
    if (source) {
        bit_location = SOURCE_REGISTER;
        operand_location = SOURCE_OPERAND;
    }

    int reg_code = strlen(inst->source);
    reg_code = (inst->source[reg_code - 1] - '0') << bit_location;

    if (found_register) {
        struct linked_list* temp_node;
        reg_code = reg_code >> REGISTER_ADDRESS;
        temp_node = get_last_node(assembler->object_list);
        code = add_bits(get_lnode_data(temp_node, int), reg_code, operand_location);
        temp_node->data = to_void_ptr(code);
        return;
    }
    code = add_bits(0, REGISTER_ADDRESS, operand_location);
    source_code->data = (to_void_ptr(code));
    insert_ll_node(assembler->object_list, to_void_ptr(reg_code));
}

void
encode_direct(struct assembler_data* assembler,
              struct line_data* inst,
              struct linked_list* source_code,
              int source)
{
    inst->source++;
    int temp = 0;
    struct bucket* temp_data;

    if ((temp = atoi(inst->source))) {
        temp = temp << 2;
        insert_ll_node(assembler->object_list, to_void_ptr(inst->source));
    } else {

        if ((temp_data =
               get_data_by_key(assembler->symbol_table, inst->source))) {
            if (strcmp(temp_data->data, MDEFINE) == 0) {
                if ((temp = atoi(temp_data->key))) {
                    temp = temp << 2;
                    insert_ll_node(assembler->object_list, to_void_ptr(temp));
                } else
                    ;
                /* error : value error */
            } else
                ;
            /* error : not a defined symbol */
        } else
            ;
        /* error : Unknown data */
    }
}

void
encode_index(struct assembler_data* assembler,
             struct line_data* inst,
             struct linked_list* source_code,
             int source,
             char* index)
{
    struct bucket* temp_data;
    int operand_location = DESTINATION_OPERAND;
    int code;
    if (source) {
        operand_location = SOURCE_OPERAND;
    }
    code = add_bits(0, INDEX_ADDRESS, operand_location);
    source_code->data = (to_void_ptr(code));
    insert_ll_node(assembler->object_list, NULL);
    int temp = 0;
    if ((temp = atoi(index))) {
        temp = temp << 2;
        insert_ll_node(assembler->object_list, to_void_ptr(temp));
    } else {
        if ((temp_data = get_data_by_key(assembler->symbol_table, index))) {
            if (strcmp(temp_data->data, MDEFINE) == 0) {
                if ((temp = atoi(temp_data->key))) {
                    temp = temp << 2;

                    insert_ll_node(assembler->object_list, to_void_ptr(temp));
                } else
                    ;
                /* error - value error */
            } else
                ;
            /* error - index is not defined */
        } else
            ;
        /* error - Unknown index*/
    }
}
void
encode_null(struct assembler_data* assembler,
            struct line_data* inst,
            struct linked_list* source_code,
            int source)
{
    int operand_location = DESTINATION_OPERAND;
    int code = 0;
    if (source) {
        operand_location = SOURCE_OPERAND;
    }
    code = add_bits(code, DIRECT_ADDRESS, operand_location);
    source_code->data = (to_void_ptr(code));
    insert_ll_node(assembler->object_list, NULL);
}
