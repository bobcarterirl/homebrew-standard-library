#include "iterator.hpp"
#include "memory.hpp"
#include "utility.hpp"


namespace hsl
{

template<typename T>
class vector
{
public:
    using value_type = T;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator = pointer;
    using size_type = size_t;


    // Element access
    reference operator[] (size_type pos) { return arr[pos]; }


    // Iterators
    iterator begin() noexcept { return arr.get(); }
    iterator end() noexcept { return arr.get() + size(); }


    // Capacity
    size_type size() const noexcept { return arr_size; }

    void reserve(size_type new_cap)
    {
        if (new_cap > arr_cap)
        {
            // We reserve the exact amount of space requested because reserve
            // is mostly used when we know (at most) how much we'll need
            unique_ptr<value_type[]> new_arr(new value_type[new_cap]);

            swap_ranges(begin(), end(), new_arr.get());
            swap(arr, new_arr);

            arr_cap = new_cap;
        }
    }


    // Modifiers
    void resize(size_type count)
    {
        reserve(count);
        arr_size = count;
    }


private:
    size_type arr_size = 0;
    size_type arr_cap = 0;
    unique_ptr<value_type[]> arr;
};

}
