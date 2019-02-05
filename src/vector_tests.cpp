#include <cassert>
#include <iostream>
#include "tests.hpp"
#include "vector.hpp"

void test_vector()
{
    std::cerr << "vector tests\n";

    std::cerr << "\tconstructors\n";
    {
        hsl::vector<int> vec1;
        assert(vec1.size() == 0);

        hsl::vector<int> vec2(5);
        assert(vec2.size() == 5);
    }

    std::cerr << "\treserve\n";
    {
        hsl::vector<int> vec;

        hsl::size_t cap = vec.capacity() + 5;
        vec.reserve(cap);
        assert(vec.capacity() >= cap);

        cap = vec.capacity();
        vec.reserve(0);
        assert(vec.capacity() == cap);
    }

    std::cerr << "\tresize\n";
    {
        hsl::vector<int> vec;
        vec.resize(5);
        assert(vec.size() == 5);
        assert(vec.capacity() >= 5);

        hsl::size_t cap = vec.capacity();
        vec.resize(0);
        assert(vec.size() == 0);
        assert(vec.capacity() == cap);
    }

    std::cerr << "\toperator[]\n";
    {
        hsl::vector<int> vec(5);
        vec[0] = 1;
        vec[4] = 5;
        assert(vec[0] == 1);
        assert(vec[4] == 5);
    }
}
