
namespace lasd {

/* ************************************************************************** */


// Specific constructors (Node)
template <typename Data>
List<Data>::Node::Node(Data&& dat) noexcept
{
    std::swap(element,dat);
}

// move constructor (Node)
template <typename Data>
List<Data>::Node::Node(Node&& nod) noexcept
{
    std::swap(element, nod.element);
    std::swap(next, nod.next);
}

/* ************************************************************************** */

// Destructor (Node)

template <typename Data>
List<Data>::Node::~Node()
{
    delete next;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool List<Data>::Node::operator==(const Node& nod)const noexcept
{
   return((element == nod.element) && 
   ((nod.next == nullptr && next == nullptr) || (nod.next != nullptr && next != nullptr)));
}

// Specific member functions (node)
template <typename Data>
typename List<Data>::Node* List<Data>::Node::Clone(Node*new_node)
{
    if(next == nullptr)
        return new_node;
    else
    {
        Node* node = new Node(element);
        node->next = next->Clone(new_node);
        return node;
    }
}


/* ************************************************************************** */
// Specific constructor (List)
template <typename Data>
List <Data>::List(const TraversableContainer<Data>& con)
{
    con.Traverse
    (
        [this](const Data& dat)
        {
            InsertAtBack(dat);
        }
    );
}

template <typename Data>
List <Data>::List(MappableContainer<Data>&& con)
{
    con.Map
    (
        [this](Data& dat)
        {
            InsertAtBack(std::move(dat));
        }
    );
}

//copy and move constructors(List)
template <typename Data>
List<Data>::List(const List<Data>& lst)
{
    if(lst.tail != nullptr)
    {
        tail = new Node(*lst.tail);
        head = lst.head->Clone(tail);
        size = lst.size;
    }
}

template <typename Data>
List<Data>::List(List<Data>&& lst) noexcept
{
    std::swap(head, lst.head);
    std::swap(tail, lst.tail);
    std::swap(size, lst.size);
}

//destructor(List)
template <typename Data>
List<Data>::~List()
{
    delete head;
}


//copy assignment
template <typename Data>
List<Data> List<Data>::operator = (const List<Data> & new_list) 
{
    Node* new_temp = new_list.head;
    Node* temp = head;
    Node* canc = nullptr;
    if(new_list.size == 0) 
    {
        delete head;
        head = tail = nullptr;
        size = 0;
    }

    while(new_temp != nullptr && temp != nullptr)
    {
        temp->element = new_temp->element;
        tail = temp;
        new_temp = new_temp->next; 
        temp = temp->next;
    }

    if (new_temp != nullptr && temp == nullptr) 
    {
        while(new_temp != nullptr) 
        {
            InsertAtBack(new_temp->element);
            new_temp = new_temp->next;
        }
        
    }
    if (new_temp == nullptr && temp != nullptr) 
    {
        size = new_list.size;
        canc = tail->next;
        delete canc;
        tail->next = nullptr;
    }
    
    return *this;
}

//move assignment
template <typename Data>
List<Data> List<Data>::operator = (List<Data> && list) noexcept 
{
    std::swap(size, list.size);
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    return *this;
}

//comparison operator
template <typename Data>
bool List<Data>::operator == (const List<Data> & list) const noexcept
{
    if (size == list.size)
    {
        Node* temp = list.head;
        for (Node* curr=head; curr!=nullptr; curr=curr->next)
        {
            if (curr->element!=temp->element)
                return false;
            temp=temp->next;
        }
        return true;
    }
    else
        return false;
} 

/* ************************************************************************** */
// Specific member functions (List)

template <typename Data>
void List<Data>::InsertAtFront(const Data& dat)
{
    Node* temp = new Node(dat);
    if(size == 0)
        tail = temp;

    temp->next = head;
    head = temp;
    size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& dat)
{
    Node* temp = new Node(std::move(dat));
    if(size == 0)
        tail = temp;
    
    temp->next = head;
    head = temp;
    size++;
}

template <typename Data>
void List<Data>::RemoveFromFront()
{
    if(size == 0)
        throw std::length_error("Access to an empty list");

    Node* temp = head;
    if(tail == head)
        head = tail = nullptr;
    else    
        head = head->next;
    size--;
    temp->next = nullptr;
    delete temp;
}

template <typename Data>
Data List<Data>::FrontNRemove()
{
    if(size == 0)
        throw std::length_error("Access to an empty list");

    Node* temp = head;
    Data val(std::move(temp->element));
    
    if(head != tail)
        head = head->next;
    else
        head = tail = nullptr;

    temp->next = nullptr;
    size--;

    delete temp;
    return val;
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& dat)
{
    Node* temp = new Node(dat);

    if(size == 0)
        head = temp;
    else
        tail->next = temp;
    
    tail = temp;
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& dat)
{
    Node* temp = new Node(std::move(dat));

    if(size == 0)
        head = temp;
    else
        tail->next = temp;
    
    tail = temp;
    size++;
}

template <typename Data>
void List<Data>::RemoveFromBack()
{
    if (size == 0)
        throw std::length_error("Access to an empty list");

    if (head == tail) 
    {
        delete tail;
        head = tail = nullptr;
    }
    else
    {
        Node* prev = head;
        while (prev->next != tail)
        {
            prev = prev->next;
        }
        delete tail;
        tail = prev;
        tail->next = nullptr;
    }
    size--;
}


template <typename Data>
Data List<Data>::BackNRemove()
{
    if (size == 0)
        throw std::length_error("Access to an empty list");
    
    Data val = std::move(tail->element);
    if (head == tail) 
    {
        delete tail;
        head = tail = nullptr;
    }
    else
    {
        Node* prev = head;
        while (prev->next != tail)
        {
            prev = prev->next;
        }
        delete tail;
        tail = prev;
        tail->next = nullptr;
    }
    size--;
    return val;
}

/* ************************************************************************** */

// Specific member functions (list) (inherited from MutableLinearContainer)

template <typename Data>
Data& List<Data>::operator[](const ulong index)
{
    if(index >= size)
        throw std::out_of_range("Access at index " + std::to_string(index));
    
    Node* curr = head;
    for(ulong i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr->element;      
}

template <typename Data>
Data& List<Data>::Front()
{
    if(size == 0)
        throw std::length_error("Access to an empty list");
    
    return head->element;
}

template <typename Data>
Data& List<Data>::Back()
{
    if (size == 0)
        throw std::length_error("Access to an empty list");
    
    return tail->element;
}


/* ************************************************************************** */

// Specific member functions (list) (inherited from LinearContainer)

template <typename Data>
const Data& List<Data>::operator[](const ulong index) const
{
    if(index >= size)
        throw std::out_of_range("Access at index " + std::to_string(index));
    
    Node* curr = head;
    for(ulong i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr->element;
}

template <typename Data>
const Data& List<Data>::Front() const
{
    if(size == 0)
        throw std::length_error("Access to an empty list");
    
    return head->element;
}

template <typename Data>
const Data& List<Data>::Back() const
{
    if(size == 0)
        throw std::length_error("Access to an empty list");
    
    return tail->element;
}

/* ************************************************************************** */

// Specific member function (inherited from MappableContainer)

template <typename Data>
void List<Data>::Map(MapFun fun) 
{
    PreOrderMap(fun, head);
}

// Specific member function (inherited from PreOrderMappableContainer)

template <typename Data>
void List<Data>::PreOrderMap(MapFun fun) 
{
    PreOrderMap(fun, head);
}

// Specific member function (inherited from PostOrderMappableContainer)

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun) 
{
    PostOrderMap(fun, head);
}

/* ************************************************************************** */

// Specific member function (list) (inherited from TraversableContainer)

template <typename Data>
void List<Data>::Traverse(TraverseFun fun) const 
{
    PreOrderTraverse(fun, head);
}

// Specific member function (list) (inherited from PreOrderTraversableContainer)

template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun) const 
{
    PreOrderTraverse(fun, head);
}

// Specific member function (list) (inherited from PostOrderTraversableContainer)

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun) const 
{
    PostOrderTraverse(fun, head);
}
/* ************************************************************************** */

// Specific member function (list) (inherited from ClearableContainer)
template <typename Data>
void List<Data>::Clear()
{
    delete head;
    head = tail = nullptr;
    size = 0;
}

/* ************************************************************************** */


// Auxiliary functions

template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun, const Node* curr) const
{
    for (; curr != nullptr; curr = curr->next)
    {
        fun(curr->element);
    }
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, const Node* curr) const
{
    if (curr != nullptr)
    {
        PostOrderTraverse(fun, curr->next);
        fun(curr->element);
    }
}

template <typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node* curr)
{
    for (; curr != nullptr; curr = curr->next)
    {
        fun(curr->element);
    }
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node* curr)
{
    if (curr != nullptr)
    {
        PostOrderMap(fun, curr->next);
        fun(curr->element);
    }
}
}
