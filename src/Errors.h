#pragma once

#include <exception>

struct DimensionsDontMatch: std::exception
{
    const char* what() const throw()
    {
        return "To perform this operation matrixes dimensions must be the same";
    }
};
