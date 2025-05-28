
namespace lasd 
{

/***************************   LINEAR CONTAINER   **********************************/
//Specific comparison operator 
template <typename Data>
bool LinearContainer<Data>::operator == (const LinearContainer<Data>& dat) const noexcept
{
   if(size == dat.size)
   {
        for(ulong i=0; i < size; i++)
        {
            if(operator[](i) != dat.operator[](i))
             return false;
     }
      return true;
  }
   else
        return false;
}

template <typename Data>
inline const Data& LinearContainer<Data>::Front() const 
{
    if (size == 0)
        throw std::length_error("The container is empty.");
    return operator[](0);
}

template <typename Data>
inline const Data& LinearContainer<Data>::Back() const 
{
    if (size == 0)
        throw std::length_error("The container is empty.");
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
void SortableLinearContainer<Data>::Sort() noexcept
{
    for (ulong i = 1; i < size; i++)
    {
        Data key = operator[](i);
        ulong j = i;
        while (j > 0 && operator[](j - 1) > key)
        {
            operator[](j) = operator[](j - 1);
            --j;
        }
        operator[](j) = key;
    }
}

}
