#include "IDs.h"

bool is_register_or_memory(ID id)
{
    return is_register(id) || is_memory(id);
}

bool is_register(ID id)
{
    return (id == ID::REGISTER_QWORD) || (id == ID::REGISTER_QWORD_ADDITIONAL) || (id == ID::REGISTER_DWORD) ||
           (id == ID::REGISTER_DWORD_ADDITIONAL) || (id == ID::REGISTER_WORD) || (id == ID::REGISTER_WORD_ADDITIONAL) ||
           (id == ID::REGISTER_BYTE) || (id == ID::REGISTER_BYTE_ADDITIONAL);
}

bool is_memory(ID id)
{
    return (id == ID::VAR_BYTE) || (id == ID::VAR_WORD) || (id == ID::VAR_DWORD) || (id == ID::VAR_QWORD);
}

bool is_byte_register(ID id)
{
    return (id == ID::REGISTER_BYTE) || (id == ID::REGISTER_BYTE_ADDITIONAL);
}

bool is_word_register(ID id)
{
    return (id == ID::REGISTER_WORD) || (id == ID::REGISTER_WORD_ADDITIONAL);
}

bool is_dword_register(ID id)
{
    return (id == ID::REGISTER_DWORD) || (id == ID::REGISTER_DWORD_ADDITIONAL);
}

bool is_qword_register(ID id)
{
    return (id == ID::REGISTER_QWORD) || (id == ID::REGISTER_QWORD_ADDITIONAL);
}

bool is_integer_number(ID id)
{
    return id == ID::INTEGER_NUMBER;
}

bool is_define_variable(ID id)
{
    return id == ID::DB || id == ID::DW || id == ID::DD || id == ID::DQ;
}