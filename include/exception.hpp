#pragma once

namespace std
{
    class exception
    {   // TODO
    public:
        virtual const char* what() const noexcept;
    };
}
