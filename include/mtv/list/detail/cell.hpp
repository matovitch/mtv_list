#pragma once

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

template <class Type>
class TCell
{
    template <class>
    friend class ::TTailList;

    template <class>
    friend class TIterator;

public:

    template <class... Args>
    TCell(TCell* tail, Args&&... args) :
        value{args...},
        _prev{tail}
    {
        if (_prev)
        {
            _prev->_next = this;
        }
    }

    Type value;

private:

    TCell* _prev = nullptr;
    TCell* _next = nullptr;
};

} // namespace detail

} // namespace list

} // namespace mtv
