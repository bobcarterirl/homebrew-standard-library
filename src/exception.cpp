#include "exception.hpp"

namespace hbstl
{

// TODO print member
const char* exception::what() const noexcept
{
    return "Error!";
}

}
