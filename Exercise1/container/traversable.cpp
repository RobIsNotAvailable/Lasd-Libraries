
namespace lasd {

/* ************************************************************************** */
// Specific member functions (TraversableContainer)

template<typename Data>
template<typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const
{
    Traverse
    (
        [fun, &acc](const Data &data)
        {
            acc = fun(data, acc);
        }
    );
    return acc;
}

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data& val) const noexcept
{
    bool exists = false;
    Traverse
    (
        [val, &exists](const Data &data)
        {
            exists |= (data == val);
        }
    );

    return exists;
}

/* ************************************************************************** */
// Specific member functions (PreOrderTraversableContainer)

template<typename Data>
template<typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun <Accumulator> fun, Accumulator acc) const
{
    PreOrderTraverse
    (
        [fun, &acc](const Data &data)
        {
            acc = fun(data, acc);
        }
    );

    return acc;
}

template<typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const
{
    PreOrderTraverse(fun);
}

// Specific member functions (PostOrderTraversableContainer)
template<typename Data>
template<typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun <Accumulator> fun, Accumulator acc) const
{
    PostOrderTraverse
    (
        [fun, &acc](const Data &data)
        {
            acc = fun(data, acc);
        }
    );

    return acc;
}

template<typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const
{
    PostOrderTraverse(fun);
}

/* ************************************************************************** */

}
