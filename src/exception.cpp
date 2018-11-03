#include "exception.hpp"

namespace std
{
    // TODO print member
    const char* exception::what() const noexcept
    {
        return "Error!";
    }
}
