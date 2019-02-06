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

template<typename T, typename Alloc = allocator<T> >
class vector
{
public:
    using value_type = T;
    using allocator_type = Alloc;
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

    vector(size_type count,
            const_reference value,
            const allocator_type& alloc = allocator_type()) :
        alloc(alloc) { assign(count, value); }

    vector(size_type count, const allocator_type& alloc = allocator_type()) :
        alloc(alloc) { resize(count); }


    // Assignment

    void assign(size_type count, const_reference value)
    {
        resize(count);
        fill(begin(), end(), value);
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

    allocator_type get_allocator() const { return alloc; }

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

    void resize(size_type count)
    {
        reserve(count);
        arr_size = count;
    }


private:
    allocator_type alloc;
    size_type arr_size = 0;
    size_type arr_cap = 0;
    unique_ptr<value_type[], function<void(pointer)> > arr;

    void delete_arr(pointer p) { alloc.deallocate(p, arr_cap); }

    void reallocate_arr(size_type new_cap)
    {
        using namespace placeholders;
        function<void(pointer)> deleter = bind(&vector::delete_arr, this, _1);
        decltype(arr) new_arr(alloc.allocate(new_cap), deleter);

        move(begin(), end(), new_arr.get());
        swap(arr, new_arr);

        arr_cap = new_cap;
    }
};


// Relational operators

template<typename T, typename Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return equal(lhs.begin(), lhs.end(), rhs.begin()); }

template<typename T, typename Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return !(lhs == rhs); }

template<typename T, typename Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    return lexicographical_compare(
            lhs.begin(), lhs.end(),
            rhs.begin(), rhs.end());
}

template<typename T, typename Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return rhs < lhs; }

template<typename T, typename Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return !(lhs > rhs); }

template<typename T, typename Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return !(lhs < rhs); }

}
