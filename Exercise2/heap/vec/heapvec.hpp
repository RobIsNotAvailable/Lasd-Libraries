
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Heap<Data>, public SortableVector<Data> 
{

protected:

  using Container::size;

public:

  // Default constructor
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  HeapVec(const TraversableContainer<Data>& con) : SortableVector<Data>(con) {if (!IsHeap()) Heapify();} // A heap obtained from a TraversableContainer
  HeapVec(MappableContainer<Data>&& con) noexcept : SortableVector<Data>(std::move(con)) {if (!IsHeap()) Heapify();} // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor and Move constructor
  HeapVec(const HeapVec<Data>& heap) : SortableVector<Data>(heap){};
  HeapVec(HeapVec<Data>&& heap) noexcept : SortableVector<Data>(std::move(heap)){};

  /* ************************************************************************ */

  // Destructor
  ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment and Move Assignment
  HeapVec<Data>& operator = (const HeapVec<Data>&);
  HeapVec<Data>& operator = (HeapVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator == (const HeapVec<Data>& heap) const noexcept {return Vector<Data>::operator == (heap);};
  inline bool operator != (const HeapVec<Data>& heap) const noexcept {return !(Vector<Data>::operator == (heap));}

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  bool IsHeap() const noexcept; // Override Heap member

  void Heapify() noexcept; // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() noexcept; // Override SortableLinearContainer member

  /* ************************************************************************ */
protected:

  // auxiliary functions

  void HeapifyDown(ulong, ulong) noexcept;
  using SortableVector<Data>::Resize;
};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
