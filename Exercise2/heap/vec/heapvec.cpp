
namespace lasd {

/* ************************************************************************** */

// Copy and Move assignment

template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator = (const HeapVec<Data>& heap)
{
    Vector<Data>::operator = (heap);
    return *this;
}

template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator = (HeapVec<Data>&& heap) noexcept
{
    Vector<Data>::operator = (std::move(heap));
    return *this;
}

template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept
{
    for (ulong i = 0; i < size; ++i)
    {
        ulong left = 2 * i + 1;
        ulong right = 2 * i + 2;

        if (left < size && (*this)[i] < (*this)[left]) // static_cast<const Vector<Data>&>(*this)[i]
           return false;
        if (right < size && (*this)[i] < (*this)[right])
            return false;
    }
    return true;
}

template <typename Data>
void HeapVec<Data>::Heapify() noexcept
{
    if (IsHeap())
        return;
    
    for (ulong i = size / 2; i-- > 0;)
    {
        MaxHeapify(i, size);
    }
}

template <typename Data>
void HeapVec<Data>::Sort() noexcept
{
    if (!IsHeap())
        Heapify();
    
    for (ulong i = size; i-- > 1; )
    {
        std::swap((*this)[0], (*this)[i]);
        MaxHeapify(0, i);
    }
}

/* ************************************************************************** */

// auxiliary functions

template <typename Data>
void HeapVec<Data>::MaxHeapify(ulong i, ulong heapSize) noexcept
{
    ulong largest = i;
    ulong left = 2 * i + 1;
    ulong right = 2 * i + 2;

    if (left < heapSize && (*this)[left] > (*this)[largest])
        largest = left;
    if (right < heapSize && (*this)[right] > (*this)[largest])
        largest = right;

    if (largest != i)
    {
        std::swap((*this)[i], (*this)[largest]);
        MaxHeapify(largest, heapSize);
    }
}

}
