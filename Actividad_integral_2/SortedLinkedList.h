#ifndef SortedLinkedList_H_INCLUDED
#define SortedLinkedList_H_INCLUDED
#include <iostream>
#include "Node.h"

using std::cout;

// Forward declaration of iterator calss
template <typename T>
class ListIterator;

template <typename T>
class SortedLinkedList
{
private:
    int list_size;
    Node<T> *head;
    Node<T> *bottom;

    // ListIterator declared as friend of the class
    // Grants LI access to SLL's private members
    friend class ListIterator<T>;

public:
    // Alias for ListIterator class
    typedef ListIterator<T> iterator;

    SortedLinkedList(): list_size{0}, head{new Node<T>{}}, bottom{new Node<T>{}}
    {
        head->next = bottom;
        bottom->prev = head;
    } 
    
	// Prints list elements
    void print()
    {
        Node<T> *i = head->next;
        while(i != bottom)
        {
            cout << i->data << " ";
            cout << "\n";
            i = i->next;  
        }
    }
    
    // TODO
    // Adds element at position determined by
    // type T's natural ordering
    // (determined by < operator)
    void add(T &element)
    {

    }  

    // Removes and returns first element
    // list should not be empty
    T remove_first()
    {
        Node<T> *r = head->next;
        head->next = r->next;
        r->next->prev = head;
        --list_size;
        T removed{r->data};
        delete r;
        return removed;
    }
    
    // TODO
    // Returns iterator to first node for which
    // predicate fun returns true
    // If no element is found, returns end iterator
    template <typename F>
    iterator find(F &fun)
    {

    }
    
    // Removes all list elements
    void clear()
    {
        while(list_size > 0)
        {
            remove_first();
        }
    }

	// Returns list's size
    int get_size()
    {
        return list_size;
    }

	// Returns true if list is empty
    // false otherwise
    bool is_empty()
    {
        return list_size == 0;
    }
    
    // Returns an iterator to first element of the list
    // If list is empty returns end iterator
    iterator begin()
    {
        return iterator{head->next};
    }

    // Returns iterator to element after last 
    // element of the list
    iterator end()
    {
        return iterator{bottom};
    }
        
	// Destructor
    ~SortedLinkedList()
    {
        clear();
        delete head;
        delete bottom;
    }  
};


// Iterator class for SortedLinkedList
template <typename T>
class ListIterator
{
private:
    // Pointer to current node of iterator
    Node<T> *current;

public:
    // Constructor
    // Current node is the one provided as argument
    ListIterator(Node<T> *i): current{i}
    {
    }

    // Overload of == operator for iterators
    bool operator==(const ListIterator<T> &rhs) const
    {
        return current == rhs.current;
    }

    // Overload of != operator for iterators
    bool operator!=(const ListIterator<T> &rhs) const
    {
        return current != rhs.current;
    }

    // Overload of * (dereference) operator for iterators
    T& operator*()
    {
        return current->data;
    }

    // Overload of ++iterator operator
    ListIterator& operator++()
    {
        current = current->next;
        return *this;
    }

    // Overload of iterator++ operator
    ListIterator operator++(int)
    {
        ListIterator<T> clone(this->current);
        current = current->next;
        return clone;
    }

    // Overload of --iterator operator
    ListIterator& operator--()
    {
        current = current->prev;
        return *this;
    }

    // Overload of iterator-- operator
    ListIterator operator--(int)
    {
        ListIterator<T> clone(this->current);
        current = current->prev;
        return clone;
    }
};

#endif // DOUBLYLINKEDLIST_H_INCLUDED
