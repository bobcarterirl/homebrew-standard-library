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

        hsl::vector<int> vec2(5, 1);
        assert(vec2.size() == 5);
        assert(vec2[0] == 1);
        assert(vec2[4] == 1);

        hsl::vector<int> vec3(5);
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

    std::cerr << "\tassign\n";
    {
        hsl::vector<int> vec1;
        vec1.assign(5, 1);
        assert(vec1.size() == 5);
        assert(vec1[0] == 1);
        assert(vec1[4] == 1);

        hsl::vector<int> vec2;
        vec2.assign(vec1.begin(), vec1.end());
        assert(vec2.size() == vec1.size());
        assert(vec2[0] == vec1[0]);
        assert(vec2[4] == vec1[0]);

        hsl::vector<int> vec3;
        vec3.assign({1, 2, 3, 4, 5});
        assert(vec3.size() == 5);
        assert(vec3[0] == 1);
        assert(vec3[4] == 5);
    }

    std::cerr << "\toperator[]\n";
    {
        hsl::vector<int> vec(5);
        vec[0] = 1;
        vec[4] = 5;
        assert(vec[0] == 1);
        assert(vec[4] == 5);
    }

    std::cerr << "\tat\n";
    {
        hsl::vector<int> vec(5);
        vec.at(0) = 1;
        vec.at(4) = 5;
        assert(vec.at(0) == 1);
        assert(vec.at(4) == 5);

        bool throws = false;
        try { vec.at(5); }
        catch (hsl::out_of_range& e) { throws = true; }
        assert(throws);
    }

    std::cerr << "\tfront, back\n";
    {
        hsl::vector<int> vec(5);
        vec.front() = 1;
        vec.back() = 5;
        assert(vec.front() == 1);
        assert(vec.back() == 5);
    }

    std::cerr << "\tdata\n";
    {
        hsl::vector<int> vec(5);
        vec[0] = 1;
        assert(*vec.data() == 1);
    }
}
