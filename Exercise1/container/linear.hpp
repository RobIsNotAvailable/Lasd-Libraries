
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderTraversableContainer<Data>, virtual public PostOrderTraversableContainer<Data>
{

  protected:

    using Container::size;

  public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment (not possible)
  LinearContainer& operator = (const LinearContainer&) = delete;
  LinearContainer& operator = (LinearContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators (possible)
  bool operator == (const LinearContainer&) const noexcept;
  inline bool operator != (const LinearContainer& con) const noexcept {return !(*this == con);}

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& operator [](ulong) const = 0;  // (non-mutable version; concrete function must throw std::out_of_range when out of range)

  inline virtual const Data& Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  inline virtual const Data& Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : virtual public LinearContainer<Data>, virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data>
{

  protected:

    using Container::size;
    using LinearContainer<Data>::operator[];
    using LinearContainer<Data>::Front;
    using LinearContainer<Data>::Back;

  public:

  // Destructor
  virtual ~MutableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment (not possible)
  MutableLinearContainer& operator = (const MutableLinearContainer&) = delete;
  MutableLinearContainer& operator = (MutableLinearContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& operator [](ulong) = 0;  // (mutable version; concrete function must throw std::out_of_range when out of range)

  inline virtual Data& Front(); // (mutable version; concrete function must throw std::length_error when empty)

  inline virtual Data& Back(); // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

};

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data>
{
  protected:

    using Container::size;
    using MutableLinearContainer<Data>::operator[];
    using MutableLinearContainer<Data>::Front;
    using MutableLinearContainer<Data>::Back;

  public:

    // Destructor
    virtual ~SortableLinearContainer() = default;

    /* ************************************************************************ */

    // Copy assignment and Move assignment (not possible)
    SortableLinearContainer& operator = (const SortableLinearContainer&) = delete;
    SortableLinearContainer& operator = (SortableLinearContainer&&) noexcept = delete;
    /* ************************************************************************ */

    // Specific member function

    virtual void Sort() noexcept;

protected:

    // Auxiliary member functions

    void QuickSort(ulong p, ulong r) noexcept;
    ulong Partition (ulong p, ulong r) noexcept;
};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
