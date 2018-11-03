#pragma once

namespace std
{
    template<typename It>
    class reverse_iterator
    {
    public:
        using iterator_type = It;
        // TODO iterator_trats<It> members

        // Constructors
        reverse_iterator();
        reverse_iterator(It it);

        // Accessors
        It base() const;

        // TODO Arithmetic operators

        // Arithmetic assignment operators
        reverse_iterator& operator++ ();
        reverse_iterator operator++ (int);
        // TODO +=, -=, --

        // Dereference operators
        decltype(*It()) operator* () const;
        // TODO ->, []

    private:
        It it;
    };


    // Relational operators

    template<typename It>
    bool operator== (const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs);

    template<typename It>
    bool operator!= (const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs);

    // TODO <, <=, >, >=


    // Template member function implementations

    // Constructors

    template<typename It>
    reverse_iterator<It>::reverse_iterator() : it() {}

    template<typename It>
    reverse_iterator<It>::reverse_iterator(It it) : it(it) {}


    // Accessors

    template<typename It>
    It reverse_iterator<It>::base() const { return it; }


    // Arithmetic assignment operators

    template<typename It>
    reverse_iterator<It>& reverse_iterator<It>::operator++ () { --it; }

    template<typename It>
    reverse_iterator<It> reverse_iterator<It>::operator++ (int)
    {
        auto temp = *this;
        --it;
        return temp;
    }


    // Dereference operators

    template<typename It>
    decltype(*It()) reverse_iterator<It>::operator* () const { return *(it-1); }


    // Template non-member function implementations

    // Relational operators

    template<typename It>
    bool operator== (const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template<typename It>
    bool operator!= (const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
    {
        return !(lhs == rhs);
    }
}
