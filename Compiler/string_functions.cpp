#include "string_functions.h"

#include <string>
#include <algorithm>

// String comparison case insensitive.
bool strcicmp(const std::string& lhs, const std::string& rhs)
{
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(), [](const char lhs, const char rhs) {
        return tolower(lhs) == tolower(rhs);
    });
}