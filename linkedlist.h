// Description: Declaration of a doubly-linked list template class

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <cstdlib>
#include <stdexcept>
#include <string>

// linkedlist node template class
template <typename T>
class Node
{
public:
  T data;
  Node<T>* prev;
  Node<T>* next;

  // default constructor
  Node(T value)
  {
    data = value;
    prev = NULL;
    next = NULL;
  }
};

// LinkedList class definition
template <typename T>
class LinkedList
{
private:
  // LinkedList private members
  int size; // size of the list
  Node<T>* front; // reference to front
  Node<T>* back;  //  reference to back

  // helper function for deep copy
  void CopyList(const LinkedList& ll);

  // helper function for deep delete
  void DeleteList();

  //#include "linkedlistprivate.h" // declare your private helper functions this file

public:
  // default constructor
  LinkedList();

  // copy constructor, performs deep copy of list elements
  LinkedList(const LinkedList& ll);

  // destructor
  ~LinkedList();

  // MUTATORS

  // insert item at front of list
  void InsertFront(T item);

  // insert item at back of list
  void InsertBack(T item);

  // insert item at position p
  void InsertAt(T item, int p);

  // remove and return item at position p
  T RemoveAt(int p);

  // append list in parameter to back of this list
  void Append(const LinkedList& ll);

  // removes duplicates from list
  void RemoveDuplicates();

  // ACCESSORS

  // return size of list
  int Size() const;

  // returns true if list is empty
  bool IsEmpty() const;

  // returns true if item exists
  bool Contains(T item) const;

  // returns item at position p
  T ElementAt(int p) const;

  // HELPERS
  bool AreEquals(Node<T>* node_A, Node<T>* node_B);

  // OVERLOADED OPERATORS

  // overloaded assignment operator
  // must work in the following cases:
  // list2 = list1 -> general case
  // list2 = list2 -> should do nothing
  LinkedList& operator=(const LinkedList& ll);
};

#include "linkedlist.cpp"

#endif