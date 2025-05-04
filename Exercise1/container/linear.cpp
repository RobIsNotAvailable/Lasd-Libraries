
namespace lasd 
{

/***************************   LINEAR CONTAINER   **********************************/

    template <typename Data>
    inline const Data& LinearContainer<Data>::Front() const 
    {
        return operator[](0);
    }

    template <typename Data>
    inline const Data& LinearContainer<Data>::Back() const 
    {
        return operator[](size - 1);
    }

    template <typename Data> 
    inline void LinearContainer<Data>::Traverse(TraverseFun fun) const
    {
        PreOrderTraverse(fun);
    }

    template <typename Data> 
    inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const
    {
        for (ulong i=0; i < size; i++)
        {
            fun(operator[](i));
        }
    }

    template <typename Data>
    inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const
    {
        for (ulong i = 1; i <= size; i++)
        {
            fun(operator[](size-i));         
        }
    }
  
/***************************   MUTABLE LINEAR CONTAINER   **********************************/

    template <typename Data>
    inline Data& MutableLinearContainer<Data>::Front() 
    {
        return operator[](0);
    }

    template <typename Data>
    inline Data& MutableLinearContainer<Data>::Back() 
    {
        return operator[](size - 1);
    }

    template <typename Data> 
    inline void MutableLinearContainer<Data>::Map(MapFun fun)
    {
        PreOrderMap(fun);
    }

    template <typename Data> 
    inline void MutableLinearContainer<Data>::PreOrderMap(MapFun fun)
    {
        for (ulong i=0; i < size; i++)
        {
            fun(operator[](i));
        }
    }

    template <typename Data>
    inline void MutableLinearContainer<Data>::PostOrderMap(MapFun fun)
    {
        for (ulong i = 1; i <= size; i++)
        {
            fun(operator[](size-i));         
        }
    }

/***************************   SORTABLE CONTAINER   **********************************/

template <typename Data>
void SortableLinearContainer<Data> :: Sort() noexcept 
{
    QuickSort(0, size-1 );
}

template <typename Data>
void SortableLinearContainer<Data> :: QuickSort (ulong p, ulong r) noexcept
{
    if (p < r)
    {
        ulong q = Partition (p, r);
        QuickSort (p, q);
        QuickSort (q+1, r);
    }
}

template <typename Data>
ulong SortableLinearContainer<Data> :: Partition (ulong p, ulong r) noexcept
{
    Data x = operator[](p);
    ulong i = p-1;
    ulong j = r+1;
    do {
        do {j--;}
        while (x < operator[](j));
        do {i++;}
        while (x > operator[](i));
        if (i<j) { std::swap (operator[](i), operator[](j)); }
    }
    while (i<j);
    return j;
}

}
