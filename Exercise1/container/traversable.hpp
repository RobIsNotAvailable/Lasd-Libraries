
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data>
{

public:

  // Destructor
  virtual ~TraversableContainer() = default;

  /* ************************************************************************ */

  // Copy and Move assignment of abstract types is not possible.
  TraversableContainer& operator = (const TraversableContainer&) = delete;
  TraversableContainer& operator=(TraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison of abstract types might be possible.
  bool operator == (const TraversableContainer&) const noexcept = delete;
  bool operator != (const TraversableContainer&) const noexcept = delete;


  /* ************************************************************************ */

  // Specific member function

  using TraverseFun = std::function<void(const Data &)>;

  virtual void Traverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator> fun, Accumulator acc) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)
  bool Exists(const Data& val) const noexcept override;
};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data>
{
  public:

  // Destructor
  virtual ~PreOrderTraversableContainer() = default; 


  /* ************************************************************************ */

  // Copy and Move assignment of abstract types is not possible.
  PreOrderTraversableContainer& operator = (const PreOrderTraversableContainer&) = delete;
  PreOrderTraversableContainer& operator = (PreOrderTraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators (might be possible)
  bool operator == (const PreOrderTraversableContainer&) const noexcept = delete;
  bool operator != (const PreOrderTraversableContainer&) const noexcept = delete; 

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PreOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  void Traverse(TraverseFun fun) const override;
};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual public TraversableContainer<Data>
{

public:

  // Destructor
  virtual ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy and Move assignment of abstract types is not possible.
  PostOrderTraversableContainer& operator = (const PostOrderTraversableContainer&) = delete;                  
  PostOrderTraversableContainer& operator = (PostOrderTraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators (might be possible)
  bool operator == (const PostOrderTraversableContainer&) const noexcept = delete;
  bool operator != (const PostOrderTraversableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PostOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  void Traverse(TraverseFun fun) const override;

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif
