
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public TraversableContainer<Data>
{

public:

  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment (not possible)
  MappableContainer& operator = (const MappableContainer&) = delete;
  MappableContainer& operator = (MappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators (not possible)
  bool operator == (const MappableContainer&) const noexcept = delete;
  bool operator != (const MappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using MapFun = std::function<void(Data &)>;

  virtual void Map (MapFun) = 0;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : virtual public MappableContainer<Data>, virtual public PreOrderTraversableContainer<Data>{

public:

  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment (not possible)
  PreOrderMappableContainer& operator = (const PreOrderMappableContainer&) = delete;
  PreOrderMappableContainer& operator = (PreOrderMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators (not possible)
  bool operator == (const PreOrderMappableContainer&) const noexcept = delete;
  bool operator != (const PreOrderMappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;
  virtual void PreOrderMap (MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  void Map (MapFun) override;

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer : virtual public MappableContainer<Data>, virtual public PostOrderTraversableContainer<Data>
{

public:

  // Destructor
  virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment (not possible)
  PostOrderMappableContainer& operator = (const PostOrderMappableContainer&) = delete;
  PostOrderMappableContainer& operator = (PostOrderMappableContainer&&) = delete;  

  /* ************************************************************************ */

  // Comparison operators (not possible)
  bool operator == (const PostOrderMappableContainer&) const noexcept = delete;
  bool operator != (const PostOrderMappableContainer&) const noexcept = delete; 

  /* ************************************************************************ */

  // Specific member function
  using typename MappableContainer<Data>::MapFun;
  virtual void PostOrderMap (MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  void Map (MapFun) override;
};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif
