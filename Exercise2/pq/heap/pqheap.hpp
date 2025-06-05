
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>, public HeapVec<Data>
{
protected:

  using Container::size;
  ulong capacity = 4;

public:

  // Default constructor
  PQHeap() {Resize(4);}

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data>& con) : HeapVec<Data>(con){capacity = size;} // A priority queue obtained from a TraversableContainer
  PQHeap(MappableContainer<Data>&& con) noexcept : HeapVec<Data>(std::move(con)){capacity = size;} // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor and Move constructor
  PQHeap(const PQHeap& pq) : HeapVec<Data>(pq) {capacity = pq.capacity;}
  PQHeap(PQHeap&& pq) noexcept : HeapVec<Data>(std::move(pq)) {std::swap(capacity, pq.capacity);}

  /* ************************************************************************ */

  // Destructor
  ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  PQHeap& operator = (const PQHeap&);
  PQHeap& operator = (PQHeap&&) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  const Data& Tip() const override; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
  Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

  void Insert(const Data&) override; // Override PQ member (Copy of the value)
  void Insert(Data&&) override; // Override PQ member (Move of the value)

  void Change(ulong, const Data&) override; // Override PQ member (Copy of the value)
  void Change(ulong, Data&&) override; // Override PQ member (Move of the value)

  void Clear() override;
  void Resize(const ulong) override;

protected:

  void HeapifyUp(ulong);
  using HeapVec<Data>::HeapifyDown;
  void Expand();
  void Reduce();
};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
