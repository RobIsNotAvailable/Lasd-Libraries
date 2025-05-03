
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd 
{

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data>
{

public:

  // Destructor
  virtual ~DictionaryContainer() = default;


  /* ************************************************************************ */

  // Copy assignment and Move assignment (not possible)
  DictionaryContainer& operator = (const DictionaryContainer&) = delete;
  DictionaryContainer& operator = (DictionaryContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators (not possible)
  bool operator == (const DictionaryContainer&) const noexcept = delete; 
  bool operator != (const DictionaryContainer&) const noexcept = delete; 

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Insert(const Data&) = 0; // Copy of the value
  virtual bool Insert(Data&&) = 0; // Move of the value
  virtual bool Remove(const Data&) = 0;// type Remove(argument) specifiers;

  inline bool InsertAll(const TraversableContainer<Data>&); // Copy of the value; From TraversableContainer; True if all are inserted
  inline bool InsertAll(MappableContainer<Data>&&); // Move of the value; From MappableContainer; True if all are inserted
  inline bool RemoveAll(const TraversableContainer<Data>&); // From TraversableContainer; True if all are removed

  inline bool InsertSome(const TraversableContainer<Data>&); // Copy of the value; From TraversableContainer; True if some is inserted
  inline bool InsertSome(MappableContainer<Data>&&); // Move of the value; From MappableContainer; True if some is inserted
  inline bool RemoveSome(const TraversableContainer<Data>&); // From TraversableContainer; True if some is removed
};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : virtual public DictionaryContainer<Data>
{
public:

  // Destructor
  virtual ~OrderedDictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment (not possible)
  OrderedDictionaryContainer& operator = (const OrderedDictionaryContainer&) = delete;
  OrderedDictionaryContainer& operator = (OrderedDictionaryContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators (not possible)
  bool operator == (const OrderedDictionaryContainer&) const noexcept = delete; 
  bool operator != (const OrderedDictionaryContainer&) const noexcept = delete; 

  /* ************************************************************************ */

  // Specific member functions
  
  const Data& Min() const = 0; // (concrete function must throw std::length_error when empty)
  Data MinNRemove() = 0; // (concrete function must throw std::length_error when empty)
  void RemoveMin() = 0; // (concrete function must throw std::length_error when empty)

  const Data& Max() const = 0; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove() = 0; // (concrete function must throw std::length_error when empty)
  void RemoveMax() = 0; // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) const = 0; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&) = 0; // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&) = 0; // (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data&) const = 0; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&) = 0; // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&) = 0; // (concrete function must throw std::length_error when not found)
};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
