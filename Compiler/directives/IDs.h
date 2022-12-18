#pragma once

enum class ID
{
    NULL_ID = -1,

    DB = 0,
    DW = 1,
    DD = 2,
    DQ = 3,

    COMMA = 5,

    ADD = 10,
    MUL = 11,
    PUSH = 12,
    POP = 13,
    IDIV = 14,

    MOV = 20,

    INTEGER_NUMBER = 100,
//    NUMBER_BYTE = 100,
//    NUMBER_WORD = 101,
//    NUMBER_DWORD = 102,
//    NUMBER_QWORD = 103,
//    NUMBER_INFINITY = 104,

    REGISTER_BYTE = 200,
    REGISTER_WORD = 201,
    REGISTER_DWORD = 202,
    REGISTER_QWORD = 203,
    REGISTER_BYTE_ADDITIONAL = 204,
    REGISTER_WORD_ADDITIONAL = 205,
    REGISTER_DWORD_ADDITIONAL = 206,
    REGISTER_QWORD_ADDITIONAL = 207,

    VAR = 500,
    VAR_BYTE = 501,
    VAR_WORD = 502,
    VAR_DWORD = 503,
    VAR_QWORD = 504,
};

bool is_register_or_memory(ID id);
bool is_register(ID id);
bool is_memory(ID id);
bool is_byte_register(ID id);
bool is_word_register(ID id);
bool is_dword_register(ID id);
bool is_qword_register(ID id);
bool is_integer_number(ID id);
bool is_define_variable(ID id);