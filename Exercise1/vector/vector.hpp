
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd 
{

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public MutableLinearContainer<Data>, public ResizableContainer
{
  protected:

    using Container::size;

    Data* Elements = nullptr;

  public:
  
    Vector() = default;

    /* ************************************************************************ */

    // Specific constructors
    Vector(const ulong); // A vector with a given initial dimension
    Vector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
    Vector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy and Move constructor
    Vector(const Vector&);
    Vector(Vector&&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~Vector();

    /* ************************************************************************ */

    // Copy and Move assignment
    Vector& operator = (const Vector&);
    Vector& operator = (Vector&&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator == (const Vector&) const noexcept;
    inline bool operator != (const Vector& vec) const noexcept {return !(*this == vec);}

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

    // Specific member function (inherited from ResizableContainer)

    void Resize(const ulong) override; // Override ResizableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    void Clear() override; // Override ClearableContainer member
};

/* ************************************************************************** */

template <typename Data>
class SortableVector : public Vector<Data>, public SortableLinearContainer<Data>
{

  protected:

    using Container::size;

    Data* Elements = nullptr;

  public:

    using Vector<Data>::operator[];

    // Default constructor
    SortableVector() = default;

    /* ************************************************************************ */

    // Specific constructors
    SortableVector(const ulong); // A vector with a given initial dimension
    SortableVector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
    SortableVector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy and Move constructor
    SortableVector(const SortableVector&);
    SortableVector(SortableVector&&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~SortableVector() = default;

    /* ************************************************************************ */

    // Copy and Move assignment
    SortableVector& operator = (const SortableVector&);
    SortableVector& operator = (SortableVector&&) noexcept;

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
