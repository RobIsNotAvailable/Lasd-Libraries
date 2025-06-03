
namespace lasd {

/* ************************************************************************** */

// Copy assignment and Move assignment

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator = (const PQHeap<Data>& pq)
{
    Vector<Data>::operator = (pq);
    capacity = pq.capacity;
    return *this;
}

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator = (PQHeap<Data>&& pq) noexcept
{
    Vector<Data>::operator = (std::move(pq));
    std::swap(capacity, pq.capacity);
    return *this;
}

/* ************************************************************************** */

// Specific member functions (inherited from PQ)

template <typename Data>
const Data& PQHeap<Data>::Tip() const
{
    if (size == 0)
        throw std::length_error("Access to an empty priority queue.");
    return (*this)[0];
}

template <typename Data>
void PQHeap<Data>::RemoveTip()
{
    if (size == 0)
        throw std::length_error("Access to an empty priority queue.");
    
    std::swap((*this)[0], (*this)[size - 1]);
    --size;
    HeapifyDown(0, size);
    Reduce();
}

template <typename Data>
Data PQHeap<Data>::TipNRemove()
{
    if (size == 0)
        throw std::length_error("Access to an empty priority queue.");
    
    Data val = std::move((*this)[0]);
    std::swap((*this)[0], (*this)[size - 1]);
    --size;
    HeapifyDown(0, size);
    Reduce();
    return val;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& val)
{
    Expand();

    ++size;
    (*this)[size - 1] = val;
    HeapifyUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& val)
{
    Expand();
    
    ++size;
    (*this)[size - 1] = std::move(val);
    HeapifyUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, const Data& val)
{
    if (index >= size)
        throw std::out_of_range("Access at index " + std::to_string(index) + "; priority queue size " + std::to_string(size));
    
    (*this)[index] = val;
    HeapifyUp(index);
    HeapifyDown(index, size);
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, Data&& val)
{
    if (index >= size)
        throw std::out_of_range("Access at index " + std::to_string(index) + "; priority queue size " + std::to_string(size));
    
    (*this)[index] = std::move(val);
    HeapifyUp(index);
    HeapifyDown(index, size);
}

// auxiliary function

template <typename Data>
void PQHeap<Data>::HeapifyUp(ulong index)
{
    while (index > 0)
    {
        ulong parent = (index - 1) / 2;
        if ((*this)[index] <= (*this)[parent])
            break;
        std::swap((*this)[index], (*this)[parent]);
        index = parent;
    }

}

template <typename Data>
void PQHeap<Data>::Expand()
{
    if (size + 1 >= capacity)
        AuxResize(capacity * 2);
}

template <typename Data>
void PQHeap<Data>::Reduce()
{
    if (size + 1 == capacity/4)
        AuxResize(capacity/2);
}

template <typename Data>
void PQHeap<Data>::AuxResize(ulong newSize)
{   
    ulong savedSize = size;
    Vector<Data>::Resize(newSize);
    size = savedSize;
    capacity = newSize;
}
}