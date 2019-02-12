#pragma once

#include "cstddef.hpp"

namespace hsl
{

using std::input_iterator_tag;
using std::iterator_traits;
using std::distance;

/*
// Iterator type tags

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};


// Iterator traits
template<typename Iter>
struct iterator_traits
{
    using difference_type = typename Iter::difference_type;
    using value_type = typename Iter::value_type;
    using pointer = typename Iter::pointer;
    using reference = typename Iter::reference;
    using iterator_category = typename Iter::iterator_category;
};

template<typename T>
struct iterator_traits<T*>
{
    using difference_type = hsl::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = random_access_iterator_tag;
};


template<typename Iter>
class reverse_iterator
{
public:
    using iterator_type = Iter;
    // TODO iterator_trats<Iter> members

    // Constructors
    reverse_iterator();
    reverse_iterator(Iter it);

    // Accessors
    Iter base() const;

    // TODO Arithmetic operators

    // Arithmetic assignment operators
    reverse_iterator& operator++ ();
    reverse_iterator operator++ (int);
    // TODO +=, -=, --

    // Dereference operators
    decltype(*Iter()) operator* () const;
    // TODO ->, []

private:
    Iter it;
};*/

using std::reverse_iterator;

// Relational operators

template<typename Iter>
bool operator== (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);

template<typename Iter>
bool operator!= (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);

// TODO <, <=, >, >=


/*template<typename T>
constexpr auto begin(T& t) -> decltype(t.begin());

template<typename T>
constexpr auto begin(const T& t) -> decltype(t.begin());

template<typename T>
constexpr auto end(T& t) -> decltype(t.end());

template<typename T>
constexpr auto end(const T& t) -> decltype(t.end());*/

using std::begin;
using std::end;
using std::cbegin;
using std::cend;
using std::rbegin;
using std::rend;
using std::crbegin;
using std::crend;

// Template member function implementations

// Constructors

/*template<typename Iter>
reverse_iterator<Iter>::reverse_iterator() : it() {}

template<typename Iter>
reverse_iterator<Iter>::reverse_iterator(Iter it) : it(it) {}


// Accessors

template<typename Iter>
Iter reverse_iterator<Iter>::base() const { return it; }


// Arithmetic assignment operators

template<typename Iter>
reverse_iterator<Iter>& reverse_iterator<Iter>::operator++ () { --it; }

template<typename Iter>
reverse_iterator<Iter> reverse_iterator<Iter>::operator++ (int)
{
    auto temp = *this;
    --it;
    return temp;
}


// Dereference operators

template<typename Iter>
decltype(*Iter()) reverse_iterator<Iter>::operator* () const { return *(it-1); }


// Template non-member function implementations

// Relational operators

template<typename Iter>
bool operator== (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
    return lhs.base() == rhs.base();
}

template<typename Iter>
bool operator!= (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) { return !(lhs == rhs); }


// begin, end

template<typename T>
constexpr auto begin(T& t) -> decltype(t.begin()) { return t.begin(); }

template<typename T>
constexpr auto begin(const T& t) -> decltype(t.begin()) { return t.begin(); }

template<typename T>
constexpr auto end(T& t) -> decltype(t.end()) { return t.end(); }

template<typename T>
constexpr auto end(const T& t) -> decltype(t.end()) { return t.end(); }*/

}
