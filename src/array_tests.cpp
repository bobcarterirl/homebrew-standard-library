#include <cassert>
#include <iostream>
#include "tests.hpp"
#include "array.hpp"

void test_array()
{
    std::cerr << "array tests\n";

    std::cerr << "\tconstructors\n";
    {
        hsl::array<int, 5> arr1;
        hsl::array<int, 5> arr2{1, 2, 3, 4, 5};
        hsl::array<int, 5> arr3 = arr2;
    }

    std::cerr << "\tempty, size, max_size\n";
    {
        hsl::array<int, 0> mtra;
        static_assert(mtra.empty(), "mtra is empty");

        hsl::array<int, 5> arr;
        static_assert(!arr.empty(), "arr isn't empty");

        static_assert(arr.size() == 5, "arr has 5 elements");
        static_assert(arr.max_size() == 5, "arr can only have 5 elements");

        hsl::array<int, 1024> big_arr;
        static_assert(big_arr.size() == 1024, "big_arr has 1024 elements");
        static_assert(big_arr.max_size() == 1024, "big_arr can only have 1024 elements");
    }

    std::cerr << "\toperator[]\n";
    {
        hsl::array<int, 5> arr;
        arr[0] = 1;
        arr[1] = 2;
        arr[4] = 3;
        assert(arr[0] == 1);
        assert(arr[1] == 2);
        assert(arr[4] == 3);

        const auto& carr = arr;
        assert(carr[0] == 1);
        assert(carr[1] == 2);
        assert(carr[4] == 3);
    }

    std::cerr << "\tat\n";
    {
        hsl::array<int, 5> arr;
        arr.at(0) = 1;
        arr.at(1) = 2;
        arr.at(4) = 3;
        assert(arr.at(0) == 1);
        assert(arr.at(1) == 2);
        assert(arr.at(4) == 3);

        const auto& carr = arr;
        assert(carr.at(0) == 1);
        assert(carr.at(1) == 2);
        assert(carr.at(4) == 3);

        bool throws_oor = false;
        try
        {
            arr.at(5);
        }
        catch (const hsl::out_of_range& oor)
        {
            throws_oor = true;
        }
        assert(throws_oor);
    }

    std::cerr << "\tfront, back\n";
    {
        hsl::array<int, 5> arr;
        arr.front() = 1;
        arr.back() = 2;
        assert(arr.front() == 1);
        assert(arr.back() == 2);

        const auto& carr = arr;
        assert(carr.front() == 1);
        assert(carr.back() == 2);
    }

    std::cerr << "\tbegin, end, cbegin, cend\n";
    {
        hsl::array<int, 5> arr;
        for (auto it = arr.begin(); it != arr.end(); it++)
        {
            assert(&*it >= &arr[0]);
            assert(&*it <= &arr[4]);

            *it = 8;
        }

        for (auto it = arr.begin(); it != arr.end(); it++)
        {
            assert(*it == 8);
        }

        const auto& carr = arr;
        for (auto it = carr.begin(); it != carr.end(); it++)
        {
            assert(&*it >= &arr[0]);
            assert(&*it <= &arr[4]);

            assert(*it == 8);
        }

        for (auto it = carr.cbegin(); it != carr.cend(); it++)
        {
            assert(&*it >= &arr[0]);
            assert(&*it <= &arr[4]);

            assert(*it == 8);
        }
    }

    std::cerr << "\tNon-member begin, end\n";
    {
        hsl::array<int, 5> arr;
        for (auto it = hsl::begin(arr); it != hsl::end(arr); it++)
        {
            assert(&*it >= &arr[0]);
            assert(&*it <= &arr[4]);

            *it = 8;
        }

        for (auto it = hsl::begin(arr); it != hsl::end(arr); it++)
        {
            assert(*it == 8);
        }
    }

    std::cerr << "\trbegin, rend, crbegin, crend\n";
    {
        hsl::array<int, 5> arr;
        for (auto it = arr.rbegin(); it != arr.rend(); it++)
        {
            assert(&*it >= &arr[0]);
            assert(&*it <= &arr[4]);

            *it = 8;
        }

        for (auto it = arr.rbegin(); it != arr.rend(); it++)
        {
            assert(*it == 8);
        }

        const auto& carr = arr;
        for (auto it = carr.rbegin(); it != carr.rend(); it++)
        {
            assert(&*it >= &arr[0]);
            assert(&*it <= &arr[4]);

            assert(*it == 8);
        }

        for (auto it = carr.crbegin(); it != carr.crend(); it++)
        {
            assert(&*it >= &arr[0]);
            assert(&*it <= &arr[4]);

            assert(*it == 8);
        }
    }

    std::cerr << "\tfill\n";
    {
        hsl::array<int, 5> arr;
        arr.fill(10);

        assert(arr == (hsl::array<int, 5>{10, 10, 10, 10, 10}));
    }

    std::cerr << "\tswap\n";
    {
        hsl::array<int, 5> arr1{1, 2, 3, 4, 5};
        hsl::array<int, 5> arr2{6, 7, 8, 9, 0};
        arr1.swap(arr2);
        assert(arr1 == (hsl::array<int, 5>{6, 7, 8, 9, 0}));
        assert(arr2 == (hsl::array<int, 5>{1, 2, 3, 4, 5}));
    }

    std::cerr << "\trelational operators\n";
    {
        hsl::array<int, 5> arr1{0, 0, 0, 0, 0};
        hsl::array<int, 5> arr2{0, 0, 0, 0, 0};
        hsl::array<int, 5> arr3{0, 0, 1, 0, 0};

        assert(arr1 == arr2);
        assert(!(arr1 == arr3));
        assert(!(arr3 == arr1));

        assert(!(arr1 != arr2));
        assert(arr1 != arr3);
        assert(arr3 != arr1);

        assert(!(arr1 < arr2));
        assert(arr1 < arr3);
        assert(!(arr3 < arr1));

        assert(arr1 <= arr2);
        assert(arr1 <= arr3);
        assert(!(arr3 <= arr1));

        assert(!(arr1 > arr2));
        assert(!(arr1 > arr3));
        assert(arr3 > arr1);

        assert(arr1 >= arr2);
        assert(!(arr1 >= arr3));
        assert(arr3 >= arr1);
    }

    std::cerr << "\tget\n";
    {
        constexpr hsl::array<int, 5> arr{1, 2, 3, 4, 5};
        static_assert(hsl::get<0>(arr) == 1, "arr[0] is 1");
        static_assert(hsl::get<1>(arr) == 2, "arr[0] is 2");
        static_assert(hsl::get<4>(arr) == 5, "arr[0] is 5");
    }

    std::cerr << "\ttuple_element, tuple_size\n";
    {
        hsl::array<int, 5> arr;
        assert((std::is_same<hsl::tuple_element<0, decltype(arr)>::type, int>::value));
        assert(hsl::tuple_size<decltype(arr)>::value == 5);
    }
}
