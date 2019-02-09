#pragma once

#include "mtv/list/detail/cell.hpp"

namespace mtv
{

template <class>
class TList;

namespace list
{

namespace detail
{

template <class>
class TIterator;

template <class Traits>
bool operator==(const TIterator<Traits>&,
                const TIterator<Traits>&);

template <class Traits>
bool operator!=(const TIterator<Traits>&,
                const TIterator<Traits>&);

template <class Traits>
class TIterator
{
    template <class>
    friend class mtv::TList;

    using Cell = typename Traits::Cell;
    using Type = typename Traits::Type;

    friend bool operator==<Traits>(const TIterator&,
                                   const TIterator&);

    friend bool operator!=<Traits>(const TIterator&,
                                   const TIterator&);
public:

    TIterator() = default;

    TIterator(Cell* cellPtr) :
        _cellPtr{cellPtr}
    {}

    TIterator(const TIterator& iterator) :
        _cellPtr{iterator._cellPtr}
    {}

    TIterator operator=(const TIterator& iterator)
    {
        _cellPtr = iterator._cellPtr;

        return *this;
    }

    Type& operator*()
    {
        return _cellPtr->value;
    }

    Type& operator->()
    {
        return _cellPtr->value;
    }

    TIterator& operator++()
    {
        _cellPtr = _cellPtr->_prev;

        return *this;
    }

    TIterator& operator++(int)
    {
        TIterator tmp{*this};
        
        operator++();

        return tmp;
    }

private:

    Cell* _cellPtr = nullptr;
};

namespace iterator
{

template <class TraitsType, class TraitsCell>
struct TTraits
{
    using Type = TraitsType;
    using Cell = TraitsCell;
};

template <class Type>
using TMake = TIterator<TTraits<Type, TCell<Type>>>;

} // namespace iterator

namespace const_iterator
{

template <class Type>
using TMake = TIterator<iterator::TTraits<const Type, const TCell<Type>>>;

} // namespace const_iterator

} // namespace detail

} // namespace list

} // namespace mtv
