#include <cassert>
#include <cstdio>
#include "tests.hpp"
#include "array.hpp"

void test_array()
{
    fprintf(stderr, "empty\n");
    {
        hbstl::array<bool, 0> mtra;
        static_assert(mtra.empty(), "mtra is empty");

        hbstl::array<int, 5> arr;
        static_assert(!arr.empty(), "arr isn't empty");
    }

    fprintf(stderr, "size, max_size\n");
    {
        hbstl::array<int, 5> arr;
        static_assert(arr.size() == 5, "arr has 5 elements");
        static_assert(arr.max_size() == 5, "arr can only have 5 elements");

        hbstl::array<int, 1024> big_arr;
        static_assert(big_arr.size() == 1024, "big_arr has 1024 elements");
        static_assert(big_arr.max_size() == 1024, "big_arr can only have 1024 elements");
    }

    fprintf(stderr, "operator[]\n");
    {
        hbstl::array<int, 5> arr;
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

    fprintf(stderr, "at\n");
    {
        hbstl::array<int, 5> arr;
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
        catch (const hbstl::out_of_range& oor)
        {
            throws_oor = true;
        }
        assert(throws_oor);
    }

    fprintf(stderr, "front, back\n");
    {
        hbstl::array<int, 5> arr;
        arr.at(0) = 1;
        arr.at(4) = 2;
        assert(arr.front() == 1);
        assert(arr.back() == 2);

        const auto& carr = arr;
        assert(carr.front() == 1);
        assert(carr.back() == 2);
    }

    fprintf(stderr, "begin, end, cbegin, cend\n");
    {
        hbstl::array<int, 5> arr;
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

    fprintf(stderr, "rbegin, rend, crbegin, crend\n");
    {
        hbstl::array<int, 5> arr;
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

    fprintf(stderr, "fill\n");
    {
        hbstl::array<int, 5> arr;
        arr.fill(10);

        for (auto i : arr)
        {
            assert(i == 10);
        }
    }

    fprintf(stderr, "relational operators\n");
    {
        hbstl::array<int, 5> arr1, arr2, arr3;

        arr1.fill(0);
        arr2.fill(0);
        arr3.fill(0);
        arr3[3] = 1;

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
}
