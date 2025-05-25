
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst : virtual public Set<Data>, virtual protected List<Data> 
{

protected:

  using Container::size;
  using typename List<Data>::Node;
  using List<Data>::head;
  using List<Data>::tail;

public:

  // Default constructor
  SetLst() = default;

  /* ************************************************************************ */

  // Specific constructors
  SetLst(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
  SetLst(MappableContainer<Data>&&) noexcept; // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor and Move constructor
  SetLst(const SetLst& set) : List<Data>(set){};
  SetLst(SetLst&& set) noexcept : List<Data>(std::move(set)){};

  /* ************************************************************************ */

  // Destructor
  ~SetLst() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  inline SetLst& operator = (const SetLst&);
  inline SetLst& operator = (SetLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator == (const SetLst& set) const noexcept {return List<Data>::operator==(set);}
  inline bool operator != (const SetLst& set) const noexcept {return !(List<Data>::operator==(set));}


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

  using List<Data>::operator[]; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

protected:

  List<Data>::Node* Find(const Data&) const;

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif
