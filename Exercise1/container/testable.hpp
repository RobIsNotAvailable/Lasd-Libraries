
#ifndef TESTABLE_HPP
#define TESTABLE_HPP

/* ************************************************************************** */

#include "container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TestableContainer : virtual public Container
{

public:

  // Destructor
  virtual ~TestableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment (not possible)
  TestableContainer& operator = (const TestableContainer&) = delete;
  TestableContainer& operator = (TestableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators (not possible)
  bool operator == (const TestableContainer&) const noexcept = delete; 
  bool operator != (const TestableContainer&) const noexcept = delete; 

  /* ************************************************************************ */

  // Specific member function
  virtual bool Exists(const Data&) const noexcept = 0;
};

/* ************************************************************************** */

}

#endif
