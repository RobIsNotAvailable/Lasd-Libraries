
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data>
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

  inline virtual const Data& Front () const; // (non-mutable version; concrete function must throw std::length_error when empty)

  inline virtual const Data& Back () const; // (non-mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse (TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data>
{

  protected:

    using Container::size;

  public:

  // Destructor
  virtual ~MutableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment (not possible)
  MutableLinearContainer& operator = (const MutableLinearContainer&) = delete;
  MutableLinearContainer& operator = (MutableLinearContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators (possible)
  bool operator == (const MutableLinearContainer&) const noexcept;
  inline bool operator != (const MutableLinearContainer& con) const noexcept { return !(*this == con); }

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& operator [](ulong) = 0;  // (mutable version; concrete function must throw std::out_of_range when out of range)

  inline virtual const Data& Front (); // (mutable version; concrete function must throw std::length_error when empty)

  inline virtual const Data& Back (); // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse (TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

};

template <typename Data>
class SortableLinearContainer : virtual public LinearContainer<Data>
{
  protected:

    using Container::size;
    using LinearContainer<Data>::operator[];

  public:

    // Destructor
    virtual ~SortableLinearContainer() = default;

    /* ************************************************************************ */

    // Copy assignment and Move assignment (not possible)
    SortableLinearContainer& operator = (const SortableLinearContainer&) = delete;
    SortableLinearContainer& operator = (SortableLinearContainer&&) noexcept = delete;
    /* ************************************************************************ */

    // Comparison operators (possible)
    bool operator == (const SortableLinearContainer&) const noexcept;
    inline bool operator != (const SortableLinearContainer&) const noexcept {return !(*this == con);}
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
