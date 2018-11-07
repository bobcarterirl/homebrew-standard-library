#pragma once

namespace hbstl
{

class exception
{   // TODO
public:
    virtual const char* what() const noexcept;
};

}
