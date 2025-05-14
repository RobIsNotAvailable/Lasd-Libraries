#include "setvec.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& con)
{
    elements = Vector<Data>(static_cast<ulong>(con.Size()));
    con.Traverse
    (
        [this](const Data& dat)
        {
            Insert(dat);
        }
    );
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& con)
{
    elements = Vector(con.Size());
    con.Map
    (
        [this](Data&& dat)
        {
            Insert(dat);
        }
    );
}

/* ************************************************************************** */

// Copy constructor and Move constructor

template <typename Data>
SetVec<Data>::SetVec(const SetVec& set)
{
    head = set.head;
    tail = set.tail;
    elements = Vector(set);
    size = set.size;
}

template <typename Data>
SetVec<Data>::SetVec(SetVec&& set) noexcept
{
    std::swap(head, set.head);
    std::swap(tail, set.tail);
    std::swap(elements, set.elements);
    std::swap(size, set.size);
}

/* ************************************************************************ */

// Copy assignment and Move assignment

template <typename Data>
SetVec<Data>& SetVec<Data>::operator = (const SetVec& set)
{
    if (this != &set)
    {
        head = set.head;
        tail = set.tail;
        elements = set.elements;
        size = set.size;
    }
    return *this;
}

template <typename Data>
SetVec<Data>& SetVec<Data>::operator = (SetVec&& set) noexcept
{
    if (this != &set)
    {
        std::swap(head, set.head);
        std::swap(tail, set.tail);
        std::swap(elements, set.elements);
        std::swap(size, set.size);
    }
    return *this;
}

/* ************************************************************************ */

// Comparison operator

template <typename Data>
bool SetVec<Data>::operator == (const SetVec& set) const noexcept
{
    if (size != set.size)
    {
        return false;
    }

    for (ulong i = 0; i < size; i++)
    {
        if ((*this)[i] != set[i])
        {
            return false;
        }
    }

    return true;
}

/* ************************************************************************ */

// Specific member functions (inherited from OrderedDictionaryContainer)

template <typename Data>
const Data& SetVec<Data>::Min() const
{
    if (size == 0)
        throw std::length_error("Access to an empty set.");

    return (*this)[0];
}

template <typename Data>
Data lasd::SetVec<Data>::MinNRemove()
{
    if (size == 0)
        throw std::length_error("Access to an empty set.");

    Data val(std::move((*this)[0]));
    ++head %= elements.Size();
    size--;
    Reduce();
    return val;
}

template <typename Data>
void SetVec<Data>::RemoveMin()
{
    if (size == 0)
        throw std::length_error("Access to an empty set.");

    ++head %= elements.Size();
    size--;
    Reduce();
}

template <typename Data>
const Data& SetVec<Data>::Max() const
{
    if (size == 0)
        throw std::length_error("Access to an empty set.");
    
    return (*this)[size - 1];
}

template <typename Data>
Data lasd::SetVec<Data>::MaxNRemove()
{
    if (size == 0)
        throw std::length_error("Access to an empty set.");
    
    Data val(std::move((*this)[size - 1]));
    tail = (tail - 1 + elements.Size()) % elements.Size();
    size--;
    Reduce();
    return val;
}

template <typename Data>
void SetVec<Data>::RemoveMax()
{
    if (size == 0)
        throw std::length_error("Access to an empty set.");

    tail = (tail - 1 + elements.Size()) % elements.Size();
    Reduce();
    size--;
}

template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& searchVal) const
{
    if (size == 0 || searchVal <= (*this)[0])
        throw std::length_error("Predecessor not found.");

    ulong i = size - 1;
    while ((*this)[i] >= searchVal)
    {
        i--;
    }
    return (*this)[i];
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& searchVal)
{
    if (size == 0 || searchVal <= (*this)[0])
        throw std::length_error("Predecessor not found.");

    ulong i = size - 1;
    while ((*this)[i] >= searchVal)
    {
        i--;
    }

    Data val = (*this)[i];

    DeleteAt(i);
    Reduce();
    size--;
    return val;
}


template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& searchVal)
{
    if (size == 0 || searchVal <= (*this)[0])
        throw std::length_error("Predecessor not found.");

    ulong i = size - 1;
    while ((*this)[i] >= searchVal)
    {
        i--;
    }

    DeleteAt(i);
    Reduce();
    size--;
}


template <typename Data>
const Data& SetVec<Data>::Successor(const Data& searchVal) const
{
    if (size == 0 || searchVal >= (*this)[size - 1])
        throw std::length_error("Successor not found.");

    ulong i = 0;
    while ((*this)[i] <= searchVal)
    {
        i++;
    }
    return (*this)[i];
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& searchVal)
{
    if (size == 0 || searchVal >= (*this)[size - 1])
        throw std::length_error("Successor not found.");
    
    ulong i = 0;
    while ((*this)[i] <= searchVal)
    {
        i++;
    }

    Data val = (*this)[i];

    DeleteAt(i);
    Reduce();
    size--;
    return val;
}


template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& searchVal)
{
    if (size == 0 || searchVal >= (*this)[size - 1])
        throw std::length_error("Successor not found.");
    
    ulong i = 0;
    while ((*this)[i] <= searchVal)
    {
        i++;
    }

    DeleteAt(i);
    Reduce();
    size--;
}

template <typename Data>
bool SetVec<Data>::Insert(const Data& val)
{
    if (Exists(val))
        return false;
    Expand();
    ulong i = 0;
    try
    {
        while (i < size && (*this)[i] < val)
        {
            i++;
        }
        MakeSpace(i);
    }
    catch (const std::out_of_range&)
    {
       ++tail %= elements.Size(); 
    }
    elements[(head + i) % elements.Size()] = val;
    size++;

    return true;
}

template <typename Data>
bool SetVec<Data>::Insert(Data&& val)
{
    if (Exists(val))
        return false;
    
    Expand();

    ulong i = 0;

    while ((*this)[i] < val)
    {
        i++;
    }
    MakeSpace(i);
    elements[(head + i) % elements.Size()] = std::move(val);
    size++;
    return true;

}

template <typename Data>
bool SetVec<Data>::Remove(const Data& searchVal)
{
    ulong i = 0;
    while ((*this)[i] < searchVal)
    {
        i++;
    }
    if ((*this)[i] != searchVal)
        return false;
    else
    {
        DeleteAt(i);
        Reduce();
        size--;
        return true;
    }
}

template <typename Data>
const Data& SetVec<Data>::operator[](const ulong i) const
{
    if(i < size)
    {
        return elements[(head + i) % elements.Size()];
    }
    else
        throw std::out_of_range("Access at index " + std::to_string(i) + "; set size" + std::to_string(size));   
}

template <typename Data>
bool SetVec<Data>::Exists(const Data& val) const noexcept
{
    ulong i = 0;
    try
    {
        while ((*this)[i] < val)
        {
            i++;
        }
        if ((*this)[i] == val)
            return true;
        else
            return false;
    }
    catch (const std::out_of_range&)
    {
        return false;
    }
}

template <typename Data>
inline void SetVec<Data>::Clear()
{
    head = tail = 0;
    AuxResize(4);
    size = 0;
}
/************************************************************* */
// Auxiliary functions 

template <typename Data>
void SetVec<Data>::DeleteAt(ulong i)
{
    while (i < size - 1)
    {
        elements[(head + i) % elements.Size()] = (*this)[i + 1];
        i++;
    }
    tail = (tail - 1 + elements.Size()) % elements.Size();
}

template <typename Data>
void SetVec<Data>::MakeSpace(ulong end)
{
    ulong i = size - 1;
    while (i >= end)
    {
        elements[(head + i + 1) % elements.Size()] = (*this)[i];
        i--;
    }
    ++tail %= elements.Size();
}

template <typename Data>
void SetVec<Data>::Expand()
{
    if (size + 1 == elements.Size())
        AuxResize(elements.Size() * 2);
}

template <typename Data>
void SetVec<Data>::Reduce()
{
    if (size + 1 == elements.Size()/4)
        AuxResize(elements.Size()/2);
}

template <typename Data>
void SetVec<Data>::AuxResize(ulong newSize)
{
    Vector<Data> tmpElements = Vector<Data>(newSize);
    for (ulong i = head, j = 0; j < size; ++i %= elements.Size(), j++)
    {
        std::swap(elements[i], tmpElements[j]);
    }
    std::swap(elements, tmpElements);
    head = 0;
    tail = size;
}


}
