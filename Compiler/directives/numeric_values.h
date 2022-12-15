#pragma once

#include "directive.h"
#include "IDs.h"

#include <sstream>

class IntegerNumber : public Directive
{
public:
    IntegerNumber() : Directive("", ID::INTEGER_NUMBER) { }

    virtual bool is_directive(const std::string& dir_name) const override
    {
        if(dir_name.empty())
            return false;

        std::stringstream ss(dir_name);
        if(dir_name[0] == '-')
        {
            int64_t value = 0;
            ss >> value;
        }
        else
        {
            uint64_t value = 0;
            ss >> value;
        }

        std::string str = ss.str();
        if(ss.fail() || !ss.eof())
            return false;

        return true;
    }
};


//class ByteValue : public IntegerNumber
//{
//public:
//    virtual ID get_id() const override
//    {
//        return ID::NUMBER_BYTE;
//    }
//
//    virtual bool check_range(int64_t value) const override
//    {
//        if((INT8_MIN <= value) && (value <= UINT8_MAX))
//            return true;
//        return false;
//    }
//};
//
//class WordValue : public IntegerNumber
//{
//public:
//    virtual ID get_id() const override
//    {
//        return ID::NUMBER_WORD;
//    }
//
//    virtual bool check_range(int64_t value) const override
//    {
//        if((INT16_MIN <= value) && (value <= UINT16_MAX))
//            return true;
//        return false;
//    }
//};
//
//class DWordValue : public IntegerNumber
//{
//public:
//    virtual ID get_id() const override
//    {
//        return ID::NUMBER_DWORD;
//    }
//
//    virtual bool check_range(int64_t value) const override
//    {
//        if((INT32_MIN <= value) && (value <= UINT32_MAX))
//            return true;
//        return false;
//    }
//};
//
//class QWordValue : public IntegerNumber
//{
//public:
//    virtual ID get_id() const override
//    {
//        return ID::NUMBER_QWORD;
//    }
//
//    virtual bool check_range(int64_t value) const override
//    {
//        if((INT64_MIN <= value) && (value <= UINT64_MAX))
//            return true;
//        return false;
//    }
//};
