#pragma once

#include "mtv/list/detail/iterator.hpp"
#include "mtv/list/detail/cell.hpp"

#include "mtv/pool/pool.hpp"

namespace mtv
{

template <class Traits>
class TList
{
    using Cell = typename Traits::Cell;
    
public:

    using CellPool       = typename Traits::CellPool;
    using const_iterator = typename Traits::const_iterator;
    using iterator       = typename Traits::      iterator;

    template <class... Args>
    void emplace_back(Args&&... args)
    {
        _tail = &(_cellPool.make(_tail, args...));
    }
    
    void pop_back()
    {
        _cellPool.recycle(*_tail);
        _tail = _tail->_prev;
    }

    iterator       end()       { return       iterator{}; }
    const_iterator end() const { return const_iterator{}; }

          iterator begin()       { return       iterator{_tail}; }
    const_iterator begin() const { return const_iterator{_tail}; }
    
    void erase(iterator& it)
    {
        Cell* const cellPtr = it._cellPtr;

        if (cellPtr == _tail)
        {
            return pop_back();
        }

        Cell* const prev = cellPtr->_prev;
        Cell* const next = cellPtr->_next;
        
        next->_prev = prev;

        if (prev)
        {
            prev->_next = next;
        }
        
        _cellPool.recycle(*cellPtr);
    }

private:

    Cell* _tail = nullptr;
    
    CellPool _cellPool;
};

namespace list
{

template <class TraitsType, std::size_t SIZE>
struct TTraits
{
    using Type = TraitsType;
    
    using Cell = TCell<Type>;
    
    using CellPool = pool::TMake<Cell, SIZE>;

    using       iterator = iterator       ::TMake<Type>;
    using const_iterator = const_iterator ::TMake<Type>;
};

template <class Type, std::size_t SIZE>
using TMake = TTailList<TTraits<Type, SIZE>>;

} // namespace list

} // namespace mtv
