
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Set<Data>, virtual public ResizableContainer
{
protected:

  ulong head = 0;
  ulong tail = 0;
  Vector<Data> elements;
  using Container::size;

public:

  // Default constructor
  SetVec() {elements = Vector<Data>(4);}

  /* ************************************************************************ */

  // Specific constructors
  SetVec(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
  SetVec(MappableContainer<Data>&&) noexcept; // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor and Move constructor
  SetVec(const SetVec&);
  SetVec(SetVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SetVec() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  SetVec& operator = (const SetVec&);
  SetVec& operator = (SetVec&&) noexcept;


  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const SetVec&) const noexcept;
  inline bool operator != (const SetVec& set) const noexcept {return !(*this == set);} 

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

 const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
 Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
 void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

 const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
 Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
 void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

 const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
 Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
 void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

 const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
 Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
 void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  
  inline void Clear() override; // Override ClearableContainer member
  void Resize(const ulong) override;

protected:
  // Auxiliary functions 
  void DeleteAt(ulong);
  void MakeSpace(ulong);
  const ulong Find(const Data&) const;

  void Expand();
  void Reduce();

};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
