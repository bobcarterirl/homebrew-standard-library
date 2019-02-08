#include "algorithm.hpp"
#include "functional.hpp"
#include "initializer_list.hpp"
#include "iterator.hpp"
#include "limits.hpp"
#include "memory.hpp"
#include "stdexcept.hpp"
#include "type_traits.hpp"
#include "utility.hpp"


namespace hsl
{

template<typename T>
class vector
{
public:
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = hsl::reverse_iterator<iterator>;
    using const_reverse_iterator = hsl::reverse_iterator<const_iterator>;


    // Constructors
    
    vector() noexcept = default;

    vector(size_type count, const_reference value)
    { assign(count, value); }

    vector(size_type count)
    { resize(count); }


    // Assignment

    void assign(size_type count, const_reference value)
    {
        fill(begin(), end(), value);
        resize(count, value);
    }

    template<typename Iter>
    enable_if_t<is_base_of_v<
            input_iterator_tag,
            typename iterator_traits<Iter>::iterator_category> >
        assign(Iter first, Iter last)
    {
        resize(last - first);
        copy(first, last, begin());
    }

    void assign(initializer_list<value_type> ilist)
    { assign(ilist.begin(), ilist.end()); }


    // Accessors

    reference at(size_type pos)
    {
        if (pos >= size()) throw out_of_range("hsl::vector::at");
        return arr[pos];
    }

    const_reference at(size_type pos) const
    {
        if (pos >= size()) throw out_of_range("hsl::vector::at");
        return arr[pos];
    }
    
    reference operator[](size_type pos) { return arr[pos]; }
    const_reference operator[](size_type pos) const { return arr[pos]; }

    reference front() { return *begin(); }
    const_reference front() const { return *begin(); }

    reference back() { return *(end() - 1); }
    const_reference back() const { return *(end() - 1); }

    pointer data() noexcept { return arr.get(); }
    const_pointer data() const noexcept { return arr.get(); }


    // Iterators

    iterator begin() noexcept { return data(); }
    const_iterator begin() const noexcept { return data(); }

    iterator end() noexcept { return data() + size(); }
    const_iterator end() const noexcept { return data() + size(); }

    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept
    { return reverse_iterator(end()); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept
    { return reverse_iterator(begin()); }

    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    const_reverse_iterator crend() const noexcept { return rend(); }


    // Capacity

    bool empty() const noexcept { return size() == 0; }
    size_type size() const noexcept { return arr_size; }
    size_type capacity() const noexcept { return arr_cap; }

    size_type max_size() const noexcept
    { return numeric_limits<size_type>::max(); }

    // We reserve the exact amount of space requested because reserve is mostly
    // used when we know (at most) how much we'll need.
    void reserve(size_type new_cap)
    { if (new_cap > arr_cap) reallocate_arr(new_cap); }

    void shrink_to_fit() { if (size < arr_cap) reallocate_arr(size); }

    
    // Modifiers

    void clear() { resize(0); }


    iterator insert(iterator pos, const_reference value)
    { return insert(pos, 1, value); }

    iterator insert(iterator pos, value_type&& value)
    {
        iterator dest = make_room(pos, 1);
        *dest = move(value);
        return dest;
    }

    iterator insert(const_iterator pos, size_type count, const_reference value)
    {
        iterator dest = make_room(pos, count);
        uninitialized_fill_n(dest, count, value);
        return dest;
    }

    template<typename Iter>
    enable_if_t<is_base_of_v<
            input_iterator_tag,
            typename iterator_traits<Iter>::iterator_category>,
            iterator>
        insert(const_iterator pos, Iter first, Iter last)
    {
        iterator dest = make_room(pos, distance(first, last));
        uninitialized_copy(first, last, dest);
        return dest;
    }

    iterator insert(const_iterator pos, initializer_list<value_type> ilist)
    { return insert(pos, ilist.begin(), ilist.end()); } 


    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args)
    {
        iterator dest = make_room(pos, 1);
        new(dest) value_type(forward<Args>(args)...);
        return dest;
    }


    iterator erase(const_iterator pos) { erase(pos, pos + 1); }

    iterator erase(const_iterator first, const_iterator last)
    {
        iterator dest = begin() + distance(begin(), first);
        move_backward(last, end(), dest);
        resize(size() - distance(first, last));
        return dest;
    }


    void push_back(const_reference value) { insert(end(), value); }
    void push_back(value_type&& value) { insert(end(), forward(value)); }

    template<typename... Args>
    reference emplace_back(Args&&... args)
    { return *emplace(end(), forward(args)...); }


    void resize(size_type count) { resize(count, value_type()); }

    void resize(size_type count, const_reference value)
    {
        if (count > size())
        {
            reserve(count);
            uninitialized_fill(end(), begin() + count, value);
        }

        arr_size = count;
    }


private:
    size_type arr_size = 0;
    size_type arr_cap = 0;
    unique_ptr<value_type[]> arr;


    // Returns capacity of array after insert or push
    // i.e. smallest power of 2 > new size
    size_type next_cap(size_type new_size)
    {
        --new_size;
        for (size_t i = 0; i < 8 * sizeof(size_type); i *= 2)
        {
            new_size |= new_size >> i;
        }

        return new_size + 1;
    }


    void reallocate_arr(size_type new_cap)
    {
        unique_ptr<value_type[]> new_arr(new value_type[new_cap]);
        move(begin(), end(), new_arr.get());

        swap(arr, new_arr);
        arr_cap = new_cap;
    }


    void make_room(const_iterator pos, size_type count)
    {
        size_type new_size = size() + count;
        size_type pos_idx = distance(begin() + pos);

        if (new_size > capacity())
        {
            size_type new_cap = next_cap(new_size);

            unique_ptr<value_type[]> new_arr(new value_type[new_cap]);
            move(begin(), pos, new_arr.get());
            move(pos, end(), new_arr.get() + pos_idx + count);

            swap(arr, new_arr);
            arr_cap = new_cap;
        }
        else
        {
            move_backward(pos, end(), begin() + pos_idx + count);
        }

        arr_size = new_size;
    }
};


// Relational operators

template<typename T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs)
{ return equal(lhs.begin(), lhs.end(), rhs.begin()); }

template<typename T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs)
{ return !(lhs == rhs); }

template<typename T>
bool operator<(const vector<T>& lhs, const vector<T>& rhs)
{
    return lexicographical_compare(
            lhs.begin(), lhs.end(),
            rhs.begin(), rhs.end());
}

template<typename T>
bool operator>(const vector<T>& lhs, const vector<T>& rhs)
{ return rhs < lhs; }

template<typename T>
bool operator<=(const vector<T>& lhs, const vector<T>& rhs)
{ return !(lhs > rhs); }

template<typename T>
bool operator>=(const vector<T>& lhs, const vector<T>& rhs)
{ return !(lhs < rhs); }

}
