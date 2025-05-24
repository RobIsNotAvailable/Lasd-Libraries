
namespace lasd
{

/* ********************************   VECTOR   ****************************************** */

// specific constructor(vector)

template <typename Data>
Vector<Data>::Vector(const ulong newSize)
{
    size = newSize;
    Elements = new Data[size]{};
}

template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& con) : Vector(con.Size())
{
    ulong i = 0;
    con.Traverse
    (
        [this, &i](const Data& dat)
        {
            Elements[i++] = dat;
        }
    );
}


template <typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& con) : Vector(con.Size())
{
    ulong i = 0;
    con.Map
    (
        [this, &i](Data& dat)
        {
            std::swap(Elements[i++], dat);
        }
    );
}

/* ************************************************************************** */

//copy constructor
template <typename Data>
Vector<Data>::Vector(const Vector& vec)
{
    size = vec.size;
    Elements = new Data[size];
    std::copy(vec.Elements, vec.Elements + size, Elements);
}

//move constructor
template <typename Data>
Vector<Data>::Vector(Vector&& vec) noexcept
{
    std::swap(size, vec.size);
    std::swap(Elements, vec.Elements);
}

/* ************************************************************************** */

//destructor(Vector)
template <typename Data>
Vector<Data>::~Vector()
{
    delete[] Elements;
}

/* ************************************************************************** */
//copy assignment (Vector)
template <typename Data>
Vector<Data>& Vector<Data>::operator = (const Vector<Data>& vec)
{
    Vector<Data>* tempv = new Vector<Data>(vec);
    std::swap(*tempv, *this);
    delete tempv;
    return *this;
}

//move assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator = (Vector<Data>&& vec) noexcept
{
    std::swap(size, vec.size);
    std::swap(Elements, vec.Elements);
    return *this;
}

/* ************************************************************************** */
//comparison operators(Vector)
template <typename Data>
bool Vector<Data>::operator == (const Vector<Data>& vec) const noexcept
{
    if(size == vec.size)
    {
        for(ulong i = 0; i < size; i++)
        {
            if(Elements[i] != vec.Elements[i])
                return false;
        }
        return true;
    }
    return false;
}

/* ************************************************************************** */
// Specific member function (inherited from MutableLinearContainer)

template <typename Data>
Data& Vector<Data>::operator[](const ulong i)
{
    if(i < size)
        return Elements[i];
    else
        throw std::out_of_range("Access at index " + std::to_string(i) + "; vector size " + std::to_string(size));
}


template <typename Data>
Data& Vector<Data>::Front()
{
    if(size != 0)
        return Elements[0];
    else
        throw std::length_error("Access to an empty vector.");
}


template <typename Data>
Data& Vector<Data>::Back()
{
    if(size != 0)
        return Elements[size - 1];
    else
        throw std::length_error("Access to an empty vector.");
}


/* ************************************************************************** */
// Specific member function (inherited from LinearContainer)

template <typename Data>
const Data& Vector<Data>::operator[](const ulong i) const
{
    if(i < size)
        return Elements[i];
    else
        throw std::out_of_range("Access at index " + std::to_string(i) + "; vector size " + std::to_string(size));
}


template <typename Data>
const Data& Vector<Data>::Front() const
{
    if(size != 0)
        return Elements[0];
    else
        throw std::length_error("Access to an empty vector.");
}


template <typename Data>
const Data& Vector<Data>::Back() const
{
    if(size != 0)
        return Elements[size - 1];
    else
        throw std::length_error("Access to an empty vector.");
}

/* ************************************************************************** */

// Specific member function (inherited from ResizableContainer)

template <typename Data>
void Vector<Data>::Resize(const ulong newSize)
{
    if(newSize == 0)
        Clear();
    else if(size != newSize)
    {
        Data* temp = new Data [newSize] {};
        ulong minSize = (size < newSize)? size : newSize;

        for(ulong i = 0; i < minSize; i++)
        {
            std::swap(Elements[i], temp[i]);
        }
        std::swap(Elements, temp);
        size = newSize;
        delete[] temp;

    }
}

/* ************************************************************************** */

// Specific member function (inherited from ClearableContainer)
template <typename Data>
void Vector<Data>::Clear()
{
    delete[] Elements;
    Elements = nullptr;
    size = 0;
}


/* ********************************   SORTABLE VECTOR   ****************************************** */

// Specific constructors

template <typename Data>
SortableVector<Data> :: SortableVector(const ulong newSize) : Vector<Data>(newSize) {}

template <typename Data>
SortableVector<Data> :: SortableVector(const TraversableContainer<Data>& con) : Vector<Data>(con){}

template <typename Data>
SortableVector<Data> :: SortableVector (MappableContainer<Data>&& con) : Vector<Data>(std::move(con)) {}

// Copy Constructor and Move Constructor
template <typename Data>
SortableVector<Data>:: SortableVector(const SortableVector<Data> & vec) : Vector<Data> (vec) {}


template <typename Data>
SortableVector<Data>:: SortableVector(SortableVector<Data> && vec) noexcept : Vector<Data> (std::move(vec)) {}


//Copy Assignment and Move Assignment

template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator= (const SortableVector<Data> & vec) 
{
    Vector<Data>::operator=(vec);
    return *this;
}

template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& vec) noexcept
{
    Vector<Data>::operator=(std::move(vec));
    return *this;
}
}
