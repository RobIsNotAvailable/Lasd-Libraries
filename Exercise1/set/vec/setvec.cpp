namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& con)
{
    elements = Vector<Data>((con.Size()));
    con.Traverse
    (
        [this](const Data& dat)
        {
            Insert(dat);
        }
    );
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& con) noexcept
{
    elements = Vector<Data>(con.Size());
    con.Map
    (
        [this](Data& dat)
        {
            Insert(std::move(dat));
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
    tail = (tail + elements.Size() - 1) % elements.Size();
    size--;
    Reduce();
    return val;
}

template <typename Data>
void SetVec<Data>::RemoveMax()
{
    if (size == 0)
        throw std::length_error("Access to an empty set.");

    tail = (tail + elements.Size() - 1) % elements.Size();
    Reduce();
    size--;
}

template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& searchVal) const
{
    if (size == 0 || searchVal <= (*this)[0])
        throw std::length_error("Predecessor not found.");

    return (*this)[Find(searchVal) - 1];
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& searchVal)
{
    if (size == 0 || searchVal <= (*this)[0])
        throw std::length_error("Predecessor not found.");

    ulong i = Find(searchVal) - 1;
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

    DeleteAt(Find(searchVal) - 1);
    Reduce();
    size--;
}


template <typename Data>
const Data& SetVec<Data>::Successor(const Data& searchVal) const
{
    if (size == 0 || searchVal >= (*this)[size - 1])
        throw std::length_error("Successor not found.");

    ulong i = Find(searchVal);
    if ((*this)[i] == searchVal)
        i++;

    return (*this)[i];
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& searchVal)
{
    if (size == 0 || searchVal >= (*this)[size - 1])
        throw std::length_error("Successor not found.");
    
    ulong i = Find(searchVal);
    if ((*this)[i] == searchVal)
        i++;

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
    
    ulong i = Find(searchVal);
    if ((*this)[i] == searchVal)
        i++;

    DeleteAt(i);
    Reduce();
    size--;
}

template <typename Data>
bool SetVec<Data>::Insert(const Data& val)
{
    Expand();

    ulong i = 0;
    try
    {
        i = Find(val);
        if ((*this)[i] == val)
            return false;

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
    Expand();

    ulong i = 0;
    try
    {
        i = Find(val);
        if ((*this)[i] == val)
            return false;
            
        MakeSpace(i);
    }
    catch (const std::out_of_range&)
    {
       ++tail %= elements.Size(); 
    }

    elements[(head + i) % elements.Size()] = std::move(val);
    size++;
    return true;

}

template <typename Data>
bool SetVec<Data>::Remove(const Data& searchVal)
{
    ulong i = Find(searchVal);
    if (size == 0 || size <= i || (*this)[i] != searchVal)
        return false;
    DeleteAt(i);
    Reduce();
    size--;
    return true;
}

template <typename Data>
const Data& SetVec<Data>::operator[](const ulong i) const
{
    if(i < size)
    {
        return elements[(head + i) % elements.Size()];
    }
    else
        throw std::out_of_range("Access at index " + std::to_string(i) + "; set size " + std::to_string(size));   
}

template <typename Data>
bool SetVec<Data>::Exists(const Data& val) const noexcept
{
    try
    {
        return ((*this)[Find(val)] == val ? true : false);
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
    if (i < size / 2)
    {
        while (i < size - 1)
        {
            elements[(head + i) % elements.Size()] = (*this)[i + 1];
            i++;
        }
        tail = (tail + elements.Size() - 1) % elements.Size();
    }
    else
    {
        while (i > 0)
        {
            elements[(head + i) % elements.Size()] = (*this)[i - 1];
            i--;
        }
        ++head %= elements.Size();
    }
}

template <typename Data>
void SetVec<Data>::MakeSpace(ulong newSpace)
{
    if (newSpace < size / 2)
    {
        head = (head + elements.Size() - 1) % elements.Size();
        for (ulong i = 0; i < newSpace; i++)
        {
            elements[(head + i) % elements.Size()] = (*this)[i + 1];
        }
    }
    else
    {
        for (ulong i = size; i > newSpace; i--)
        {
            elements[(head + i) % elements.Size()] = (*this)[i - 1];
        }
        ++tail %= elements.Size();
    }
}

template <typename Data>
const ulong SetVec<Data>::Find(const Data& val) const
{
    ulong left = 0;
    ulong right = size;

    while (left < right)
    {
        ulong mid = left + (right - left) / 2;
        const Data& midVal = (*this)[mid];

        if (midVal == val)
            return mid;
        else if (midVal < val)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
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
    for (ulong i = head, j = 0; j < newSize; ++i %= elements.Size(), j++)
    {
        std::swap(elements[i], tmpElements[j]);
    }
    std::swap(elements, tmpElements);
    head = 0;
    tail = size;
}


}
