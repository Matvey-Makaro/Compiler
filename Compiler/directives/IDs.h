#pragma once

enum class ID
{
    NULL_ID = -1,

    DB = 0,
    DW = 1,

    COMMA = 5,

    ADD = 10,
    MUL = 11,
    PUSH = 12,
    POP = 13,
    IDIV = 14,

    MOV = 20,

    NUMBER_BYTE = 100,
    NUMBER_WORD = 101,
    NUMBER_INFINITY = 102,

    REGISTER_BYTE = 200,
    REGISTER_WORD = 201,

    VAR = 500,
    VAR_BYTE = 501,
    VAR_WORD = 502
};
