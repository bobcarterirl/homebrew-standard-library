#include <cassert>
#include <iostream>
#include "tests.hpp"
#include "vector.hpp"

void test_vector()
{
    std::cerr << "vector tests\n";

    hsl::vector<int> vec;
    vec.resize(5);
    vec[0] = 1;
    vec[4] = 5;
    assert(vec[0] == 1);
    assert(vec[4] == 5);

    std::cerr << "\tconstructors\n";
    {
        hsl::vector<int> vec;
    }

    std::cerr << "\treserve\n";
    {
        hsl::vector<int> vec;
        vec.reserve(10);
    }
}
