#include "directive.h"
#include "../string_functions.h"

#include <string>
#include <set>
#include <utility>

Directive::Directive(const std::string& directive_name, ID directive_id) :
        name(directive_name), id(directive_id)
{ }

ID Directive::get_id() const
{
    return id;
}

bool Directive::is_directive(const std::string& dir_name) const
{
    return strcicmp(name, dir_name);
}
