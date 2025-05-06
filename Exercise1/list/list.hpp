
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public MutableLinearContainer<Data>, virtual public ClearableContainer
{

protected:

  using Container::size;

  struct Node 
  {

    Data element;
    Node* next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    inline Node (const Data & dat) : element(dat) {};
    inline Node (Data&&) noexcept;

    /* ********************************************************************** */

    // Copy constructor and Move constructor
    inline Node (const Node & nod) : element(nod.element) {};
    inline Node (Node&& nod) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
    bool operator == (const Node&) const noexcept;
    inline bool operator != (const Node& nod) const noexcept {return !(*this == nod);}

    /* ********************************************************************** */

    // Specific member functions

    virtual Node* Clone(Node*);

  };

  Node* head = nullptr;
  Node* tail = head;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data>&); // A list obtained from a TraversableContainer
  List(MappableContainer<Data>&&); // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor and Move constructor
  List(const List&);
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  List operator = (const List&);
  List operator = (List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const List&) const noexcept;
  inline bool operator != (const List& lst) const noexcept {return !(*this == lst);}

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&); // Copy of the value
  void InsertAtFront(Data&&);      // Move of the value
  void RemoveFromFront();          // (must throw std::length_error when empty)
  Data FrontNRemove();             // (must throw std::length_error when empty)

  void InsertAtBack(const Data&); // Copy of the value
  void InsertAtBack(Data&&);      // Move of the value
  void RemoveFromBack();          // (must throw std::length_error when empty)
  Data BackNRemove();             // (must throw std::length_error when empty) 
  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  Data& operator[](const ulong) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  Data& Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  Data& Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  const Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member


  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear () override; // Override ClearableContainer member

  protected:

  // Auxiliary functions
  void PreOrderTraverse(TraverseFun, const Node*) const;
  void PostOrderTraverse(TraverseFun, const Node*) const;


  void PreOrderMap(MapFun, Node*);
  void PostOrderMap(MapFun, Node*);
};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
