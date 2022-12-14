#pragma once

#include <string>

template<typename T>
class CaseInsensLess
{
public:
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        size_t min_size = std::min(lhs.size(), rhs.size());
        for (size_t i = 0; i < min_size; i++)
        {
            auto lhs_low = tolower(lhs[i]);
            auto rhs_low = tolower(rhs[i]);
            if (lhs_low != rhs_low)
                return lhs_low < rhs_low;
        }

        return lhs.size() < rhs.size();
    }
};

bool strcicmp(const std::string& lhs, const std::string& rhs);