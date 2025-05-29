
#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : public virtual SortableLinearContainer<Data>, public virtual ClearableContainer {

public:

  // Destructor
  virtual ~Heap() = default;

  /* ************************************************************************ */

  // Copy assignment
  Heap& operator = (const Heap&) = delete; // Copy assignment of abstract types is not possible.
  Heap& operator = (Heap&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual bool IsHeap() const noexcept = 0;
  virtual void Heapify() noexcept = 0;

};

/* ************************************************************************** */

}

#endif
