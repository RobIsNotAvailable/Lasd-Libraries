
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

namespace lasd 
{

/* ************************************************************************** */

class Container 
{
  protected:

    // Default constructor
    Container() = default;

    ulong size = 0;

  public:

    // Destructor
    virtual ~Container() = default;

    /* ************************************************************************ */

    // Copy assignment and Move assignment (not possible)
    Container& operator = (const Container&) = delete;
    Container& operator = (Container&&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators (not possible)
    bool operator == (const Container&) const noexcept = delete; 
    bool operator != (const Container&) const noexcept = delete; 

    /* ************************************************************************ */

    // Specific member functions
    virtual inline bool Empty() const noexcept
    {
      return(size == 0);
    }

    virtual inline ulong Size() const noexcept
    {
      return size;
    } 

};

/* ************************************************************************** */

class ClearableContainer : virtual public Container 
{
  public:

    // Destructor
    virtual ~ClearableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment and Move assignment (not possible)
    ClearableContainer& operator = (const ClearableContainer&) = delete;
    ClearableContainer& operator = (ClearableContainer&&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators (not possible)
    bool operator == (const ClearableContainer&) const noexcept = delete; 
    bool operator != (const ClearableContainer&) const noexcept = delete; 

    /* ************************************************************************ */

    // Specific member functions

    virtual inline void Clear()
    {
      size = 0;
    }

};

/* ************************************************************************** */

class ResizableContainer : virtual public ClearableContainer
{
  private:

  protected:

  public:

    // Destructor
    virtual ~ResizableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment and Move assignment (not possible)
    ResizableContainer& operator = (const ResizableContainer&) = delete;
    ResizableContainer& operator = (ResizableContainer&&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators (not possible)
    bool operator == (const ResizableContainer&) const noexcept = delete; 
    bool operator != (const ResizableContainer&) const noexcept = delete; 

    /* ************************************************************************ */

    // Specific member functions

    virtual inline void Resize(ulong newSize)
    {
      size = newSize;
    }

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    virtual inline void Clear()
    {
      Resize(0);
    }

};

/* ************************************************************************** */

}

#endif
