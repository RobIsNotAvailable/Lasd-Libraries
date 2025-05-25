
namespace lasd {

/* ************************************************************************** */
// Specific constructors
template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& con)
{
    con.Traverse
    (
        [this](const Data& dat)
        {
            Insert(dat);
        }
    );
}

template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& con) noexcept
{
    con.Map
    (
        [this](Data& dat)
        {
            Insert(std::move(dat));
        }
    );
}


/* ************************************************************************** */

// Copy assignment and Move assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator = (const SetLst<Data>& set)
{
    List<Data>::operator=(set);
    return *this;
}

template <typename Data>
SetLst<Data>& SetLst<Data>::operator = (SetLst<Data>&& set) noexcept 
{
    List<Data>::operator=(std::move(set));
    return *this;
}

template <typename Data>
const Data& SetLst<Data>::Min() const
{
    return List<Data>::Front();
}

template <typename Data>
Data SetLst<Data>::MinNRemove()
{
    return List<Data>::FrontNRemove(); 
}

template <typename Data>
void SetLst<Data>::RemoveMin()
{
    return List<Data>::RemoveFromFront();
}

template <typename Data>
const Data& SetLst<Data>::Max() const
{
    return List<Data>::Back();
}

template <typename Data>
Data SetLst<Data>::MaxNRemove()
{
    return List<Data>::BackNRemove();
}

template <typename Data>
void SetLst<Data>::RemoveMax()
{
    return List<Data>::RemoveFromBack();
}

template <typename Data>
const Data& SetLst<Data>::Predecessor(const Data& searchVal) const
{
    if (size == 0 || searchVal <= head->element)
        throw std::length_error("Predecessor not found.");

    Node* found = Find(searchVal);
    if (found && found->element != searchVal)
        return found->element;
    
    Node* prev = head;
    while (prev->next != found)
    {
        prev = prev->next;
    }
    return prev->element;
}

template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data& searchVal)
{
    if (size == 0 || searchVal <= head->element)
        throw std::length_error("Predecessor not found.");

    Node* found = Find(searchVal);
    Node* prev = head;

    if (found->element == searchVal)
    {
        if (head->next == found)
            return List<Data>::FrontNRemove();
        while (prev->next->next != found)
        {
            prev = prev->next;
        }
    }
    else
    {
        if (found == head)
            return List<Data>::FrontNRemove();
        if (found == tail)
            return List<Data>::BackNRemove();
        while (prev->next != found)
        {
            prev = prev->next;
        }
    }
    found = prev->next;
    Data val = std::move(found->element);
    prev->next = found->next;
    found->next = nullptr;
    delete found;
    size--;
    return val;
}


template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data& searchVal)
{
    if (size == 0 || searchVal <= head->element)
        throw std::length_error("Predecessor not found.");

    Node* found = Find(searchVal);
    Node* prev = head;

    if (found->element == searchVal)
    {
        if (head->next == found)
            return List<Data>::RemoveFromFront();
        while (prev->next->next != found)
        {
            prev = prev->next;
        }
    }
    else
    {
        if (found == head)
            return List<Data>::RemoveFromFront();
        if (found == tail)
            return List<Data>::RemoveFromBack();
        while (prev->next != found)
        {
            prev = prev->next;
        }
    }
    found = prev->next;
    prev->next = found->next;
    found->next = nullptr;
    delete found;
    size--;
}


template <typename Data>
const Data& SetLst<Data>::Successor(const Data& searchVal) const
{
    if (size == 0 || searchVal >= tail->element)
        throw std::length_error("Successor not found.");
    
    Node* found = Find(searchVal);
    return (found ? found->next->element : head->element);
}

template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& searchVal)
{
    if (size == 0 || searchVal >= tail->element)
        throw std::length_error("Successor not found.");

    Node* found = Find(searchVal);
    if (!found)
        return List<Data>::FrontNRemove();
    
    Node* succ = found->next;
    if (succ == tail)
        return List<Data>::BackNRemove();

    found->next = succ->next;
    succ->next = nullptr;

    Data val = std::move(succ->element);
    delete succ;
    size--;
    return val;
}


template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& searchVal)
{
    if (size == 0 || searchVal >= tail->element)
        throw std::length_error("Successor not found.");

    Node* found = Find(searchVal);
    if (!found)
        return List<Data>::RemoveFromFront();
    
    Node* succ = found->next;
    if (succ == tail)
        return List<Data>::RemoveFromBack();
    
    found->next = succ->next;
    succ->next = nullptr;

    delete succ;
    size--;
}
/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
bool SetLst<Data>::Insert(const Data& val)
{
    Node* found = Find(val);
    if (found && found->element == val)
        return false;
    
    if (found == nullptr)
        List<Data>::InsertAtFront(val);
    else if (found == tail)
        List<Data>::InsertAtBack(val);
    else
    {
        Node* nuovo = new Node(val);
        nuovo->next = found->next;
        found->next = nuovo;
        size++;
    }
    return true;
}

template <typename Data>
bool SetLst<Data>::Insert(Data&& val)
{
    Node* found = Find(val);
    if (found && found->element == val)
        return false;
    
    if (found == nullptr)
        List<Data>::InsertAtFront(std::move(val));
    else if (found == tail)
        List<Data>::InsertAtBack(std::move(val));
    else
    {
        Node* nuovo = new Node(std::move(val));
        nuovo->next = found->next;
        found->next = nuovo;
        size++;
    }
    return true;
}

template <typename Data>
bool SetLst<Data>::Remove(const Data& val)
{
    Node* found = Find(val);
    if (!found || found->element != val)
        return false;
    
    if (found == head)
        List<Data>::RemoveFromFront();
    else if (found == tail)
        List<Data>::RemoveFromBack();
    else
    {
        Node* prev = head;
        while (prev->next != found)
        {
            prev = prev->next;
        }
        prev->next = found->next;
        found->next = nullptr;
        delete found;
        size--;
    }
    return true;
}

/* ************************************************************************** */

// Specific member function (inherited from TestableContainer)


template <typename Data>
bool SetLst<Data>::Exists(const Data& val) const noexcept
{
    Node* found = Find(val);
    if (!found || found->element != val)
        return false;
    return true;
}
/************************************************************* */
// Auxiliary functions 


template <typename Data>
SetLst<Data>::Node* SetLst<Data>::Find(const Data& val) const
{
    Node* left = head;
    Node* curr = nullptr;

    ulong length = size;

    while (length > 0) 
    {
        ulong steps = length / 2;
        Node* mid = left;

        for (ulong i = 0; i < steps; ++i) 
        {
            mid = mid->next;
        }

        if (mid->element == val) 
        {
            return mid;
        }
        else if (mid->element < val)
        {
            curr = mid;
            left = mid->next;
            length = length - steps - 1;
        }
        else 
            length = steps;
    }

    return curr;
}

}

