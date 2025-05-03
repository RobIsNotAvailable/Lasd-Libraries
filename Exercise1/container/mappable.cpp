
namespace lasd {

/* ************************************************************************** */

// specific member functions (PreOrderMappableContainer)

template<typename Data>
inline void PreOrderMappableContainer<Data> :: Map(MapFun fun)
{
    PreOrderMap(fun);
}

// specific member functions (PostOrderMappableContainer)

template<typename Data>
inline void PostOrderMappableContainer<Data> :: Map(MapFun fun)
{
    PostOrderMap(fun);
}
/* ************************************************************************** */

}
