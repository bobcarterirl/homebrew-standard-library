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

template<typename T, typename Alloc = allocator<T>>
class vector
{
private:
    using AT = allocator_traits<Alloc>;

public:
    using value_type = T;
    using allocator_type = Alloc;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename AT::pointer;
    using const_pointer = typename AT::const_pointer;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = hsl::reverse_iterator<iterator>;
    using const_reverse_iterator = hsl::reverse_iterator<const_iterator>;


    // Constructors
    
    vector() noexcept(noexcept(allocator_type())) :
        vector(allocator_type())
    {}

    explicit vector(const allocator_type& alloc) noexcept :
        alloc(alloc),
        arr_size(0),
        arr_cap(0)
    {}


    vector(size_type count, const_reference value,
            const allocator_type& alloc = allocator_type()) :
        alloc(alloc),
        arr_size(count),
        arr_cap(count),
        arr(allocate(count))
    { uninitialized_fill_n_a(begin(), count, value); }

    explicit vector(size_type count,
            const allocator_type& alloc = allocator_type()) :
        alloc(alloc),
        arr_size(count),
        arr_cap(count),
        arr(allocate(count))
    { uninitialized_value_construct_a(begin(), end()); }

    template<typename Iter,
            typename = enable_if_t<is_base_of_v<
                input_iterator_tag,
                typename iterator_traits<Iter>::iterator_category>>>
    vector(Iter first, Iter last,
            const allocator_type& alloc = allocator_type()) :
        alloc(alloc),
        arr_size(distance(first, last)),
        arr_cap(distance(first, last)),
        arr(allocate(distance(first, last)))
    { uninitialized_copy_a(first, last, begin()); }

    vector(const vector& other) :
        vector(other.begin(), other.end())
    {}

    vector(const vector& other, const allocator_type& alloc) :
        vector(other.begin(), other.end(), alloc)
    {}

    vector(vector&& other) noexcept :
        alloc(move(other.alloc)),
        arr_size(other.arr_size),
        arr_cap(other.arr_cap),
        arr(move(other.arr))
    {
        other.arr_size = 0;
        other.arr_cap = 0;
    }

    vector(vector&& other, const allocator_type& alloc) :
        alloc(alloc),
        arr_size(other.arr_size),
        arr_cap(other.arr_cap)
    {
        if (alloc == other.alloc)
        {
            arr = move(other.arr);
            other.arr_size = 0;
            other.arr_cap = 0;
        }
        else
        {
            arr = allocate(capacity());
            arr = move(other.begin(), other.end(), begin());
        }
    }

    vector(initializer_list<value_type> ilist,
            const allocator_type& alloc = allocator_type()) :
        vector(ilist.begin(), ilist.end())
    {}


    // Assignment

    void assign(size_type count, const_reference value)
    {
        arr_size = count;
        arr_cap = count;
        arr = allocate(count);
        uninitialized_fill_n_a(begin(), count, value);
    }

    template<typename Iter>
    enable_if_t<is_base_of_v<
            input_iterator_tag,
            typename iterator_traits<Iter>::iterator_category> >
        assign(Iter first, Iter last)
    {
        size_type dist = distance(first, last);
        arr_size = dist;
        arr_cap = dist;
        arr = allocate(dist);
        uninitialized_copy_a(first, last, begin());
    }

    void assign(initializer_list<value_type> ilist)
    { assign(ilist.begin(), ilist.end()); }


    vector& operator=(const vector& other)
    {
        assign(other.begin(), other.end());
        return *this;
    }

    vector& operator=(vector&& other)
    {
        arr_size = other.arr_size;
        arr_cap = other.arr_cap;
        arr = move(other.arr);

        other.arr_size = 0;
        other.arr_cap = 0;

        return *this;
    }


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

    reference front() { return arr[0]; }
    const_reference front() const { return arr[0]; }

    reference back() { return arr[size() - 1]; }
    const_reference back() const { return arr[size() - 1]; }

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
    { return const_reverse_iterator(end()); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept
    { return const_reverse_iterator(begin()); }

    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    const_reverse_iterator crend() const noexcept { return rend(); }


    // Capacity

    bool empty() const noexcept { return size() == 0; }
    size_type size() const noexcept { return arr_size; }
    size_type capacity() const noexcept { return arr_cap; }

    size_type max_size() const noexcept
    { return numeric_limits<size_type>::max(); }

    void reserve(size_type new_cap)
    { if (new_cap > capacity()) reallocate_arr(new_cap); }

    void shrink_to_fit() { if (size() < capacity()) reallocate_arr(size()); }

    
    // Modifiers

    void clear() { resize(0); }


    iterator insert(const_iterator pos, const_reference value)
    { return insert(pos, 1, value); }

    iterator insert(const_iterator pos, value_type&& value)
    {
        iterator dest = make_room(pos, 1);
        *dest = move(value);
        return dest;
    }

    iterator insert(const_iterator pos, size_type count, const_reference value)
    {
        iterator dest = make_room(pos, count);
        uninitialized_fill_n_a(dest, count, value);
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
        uninitialized_copy_a(first, last, dest);
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
    void push_back(value_type&& value)
    { insert(end(), forward<value_type&&>(value)); }

    template<typename... Args>
    reference emplace_back(Args&&... args)
    { return *emplace(end(), forward<Args>(args)...); }

    void pop_back() { resize(arr_size - 1); }


    void resize(size_type count)
    {
        if (count > size())
        {
            reserve(count);
            uninitialized_value_construct_a(end(), begin() + count);
        }

        arr_size = count;
    }

    void resize(size_type count, const_reference value)
    {
        if (count > size())
        {
            reserve(count);
            uninitialized_fill_a(end(), begin() + count, value);
        }

        arr_size = count;
    }


    void swap(vector& other)
    {
        hsl::swap(arr_size, other.arr_size);
        hsl::swap(arr_cap, other.arr_cap);
        hsl::swap(arr, other.arr);
    }


private:
    using Array_type = unique_ptr<value_type[], function<void(pointer)>>;

    allocator_type alloc;
    size_type arr_size;
    size_type arr_cap;
    Array_type arr;

    Array_type allocate(size_type n)
    {
        auto del = [this, n](T* p)
        {
            for (size_type i = 0; i < n; ++i)
            {
                AT::destroy(this->alloc, p + i);
            }
            AT::deallocate(this->alloc, p, n);
        };

        return Array_type(AT::allocate(this->alloc, n), del);
    }


    // Returns capacity of array after insert or push
    // i.e. smallest power of 2 > new size
    size_type next_cap(size_type new_size)
    {
        --new_size;
        for (size_t i = 1; i < 8 * sizeof(size_type); i *= 2)
        {
            new_size |= new_size >> i;
        }

        return new_size + 1;
    }


    // Reallocates underlying array w/ new capacity
    void reallocate_arr(size_type new_cap)
    {
        Array_type new_arr(allocate(new_cap));
        move(begin(), end(), new_arr.get());

        hsl::swap(arr, new_arr);
        arr_cap = new_cap;
    }

    // Makes room for insert or push by moving elements to the right and
    // reallocating, if necessary
    iterator make_room(const_iterator pos, size_type count)
    {
        size_type new_size = size() + count;
        size_type pos_idx = distance(cbegin(), pos);

        if (new_size > capacity())
        {
            size_type new_cap = next_cap(new_size);

            Array_type new_arr(allocate(new_cap));
            uninitialized_move_a(cbegin(), pos, new_arr.get());
            uninitialized_move_a(pos, cend(), new_arr.get() + pos_idx + count);

            hsl::swap(arr, new_arr);
            arr_cap = new_cap;
        }
        else if (count >= (size_type)distance(pos, cend()))
        {
            uninitialized_move_a(pos, cend(), begin() + pos_idx + count);
        }
        else
        {
            uninitialized_move_a(cend() - count, cend(), end());
            move_backward(pos, cend() - count, end());
        }

        arr_size = new_size;

        return begin() + pos_idx;
    }


    void uninitialized_value_construct_a(iterator first, iterator last)
    {
        for (; first != last; ++first)
        {
            AT::construct(alloc, first);
        }
    }

    void uninitialized_fill_n_a(iterator first, size_type count,
            const_reference value)
    {
        iterator last = first + count;
        for (; first != last; ++first)
        {
            AT::construct(alloc, first, value);
        }
    }

    void uninitialized_copy_a(const_iterator first, const_iterator last,
            iterator dest)
    {
        for (; first != last; ++first, ++dest)
        {
            AT::construct(alloc, dest, *first);
        }
    }

    void uninitialized_move_a(const_iterator first, const_iterator last,
            iterator dest)
    {
        for(; first != last; ++first, ++dest)
        {
            AT::construct(alloc, dest, move(*first));
        }
    }
};


// Deduction guide

template<typename Iter,
        typename Alloc = allocator<typename iterator_traits<Iter>::value_type>>
vector(Iter, Iter)
    -> vector<typename iterator_traits<Iter>::value_type, Alloc>;


// Relational operators

template<typename T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs)
{
    return lhs.size() == rhs.size()
        && equal(lhs.begin(), lhs.end(), rhs.begin());
}

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


// Swap specialization

template<typename T>
void swap(vector<T>& lhs, vector<T>& rhs)
    noexcept(noexcept(lhs.swap(rhs)))
{ lhs.swap(rhs); }

}
