#pragma once

#include "exception.hpp"

namespace std
{
    class logic_error : public exception
    {   // TODO
    };

    class out_of_range : public logic_error
    {
    public:
        explicit out_of_range(const char* what_arg);
    };
}
