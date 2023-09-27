#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL
using namespace std;

template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

   List() : first(nullptr), last(nullptr), size_list(0) {
        
   }

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
      if (size_list == 0) {
          return true;
      }
      return false;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
      return size_list;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T& front() {
      assert(!empty());
      return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T& back() {
      assert(!empty());
      return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T& datum) {
      Node* temp = first; //pointer that points to current first node
      first = new Node(); //first pointer now points to a new node
      first->prev = nullptr; 
      first->next = temp; //the original first node is after the new first node
      first->datum = datum;
      if (temp != nullptr) {
          //the previous of the original first node is the current first node
          temp->prev = first; 
          
      }
      else {
          last = first;
      }
      ++size_list;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T& datum) {
      Node* temp = last; //pointer that points to current last node
      last = new Node(); //last pointer onw points to a new node
      last->prev = temp; //the original last node is before the new last node
      last->next = nullptr;
      last->datum = datum;
      if (temp != nullptr) {
          //the next of the original last node is the current last node
          temp->next = last;
      }
      else {
          first = last;
      }
      ++size_list;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
      assert(!empty());
      Node* temp = first->next; //pointer that points to the second node
      delete first; //deletes first node
      if (temp != nullptr) {
          //set the prev of second node to nullptr since it is now the first node
          temp->prev = nullptr;
          first = temp;
      }
      else {
          first = nullptr;
          last = nullptr;
      }
      --size_list;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
     assert(!empty());
     //pointer that points to second to last node;
     Node* temp = last->prev; 
     delete last; //deletes last node
     if (temp != nullptr) {
         //sets the next of the second to last node to ptr since it is now the last node
         temp->next = nullptr; 
         last = temp;
     }
     else {
         first = nullptr;
         last = nullptr;
     }
     --size_list;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
      while (!empty()) {
          pop_front();
      }
  }

  //overloaded assigment operator
  List& operator=(const List<T>& rhs) {
      if (this == &rhs) {
          return *this;
      }
      clear();
      copy_all(rhs);
      return *this;
  }

  //copy constructor
  List(const List<T>& other) {
      first = nullptr;
      last = nullptr;
      size_list = 0;
      copy_all(other);
  }

  ~List() {
      clear();
  }
  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T>& other) {
      assert(empty());
      Node* temp = other.first; //pointer that points to other's first node
      while (temp != nullptr) {
          push_back(temp->datum); //adds the node to the back of this list
          temp = temp->next; //pointer now points to the next node of other
      }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int size_list;

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    Iterator() : node_ptr(nullptr) {

    }

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T& operator*() {
        assert(node_ptr);
        return node_ptr->datum;
    }

    Iterator& operator++() {
        assert(node_ptr);
        node_ptr = node_ptr->next;
        return *this;
    }

    bool operator==(const Iterator& rhs) const{
        if (node_ptr == rhs.node_ptr) {
            return true;
        }
        return false;
    }

    bool operator!=(const Iterator& rhs) const{
        if (node_ptr == rhs.node_ptr) {
            return false;
        }
        return true;
    }

  
  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend List;


    // construct an Iterator at a specific position
    Iterator(Node* p) {
        node_ptr = p;
    }


  };//List::Iterator
  ////////////////////////////////////////
  // return an Iterator pointing to the first element

  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
      Iterator temp;
      return temp;
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
      Node* temp = i.node_ptr;
      Node* before = temp->prev;
      Node* after = temp->next;
      delete temp;
      if (before) {
          before->next = after;
          
      }
      else {
          first = after;
      }
      if (after) {
          after->prev = before;
      }
      else {
          last = before;
      }
      --size_list;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T& datum) {
      Node* after = i.node_ptr;
      if (after == nullptr) {
          push_back(datum);
          return;
      }
      Node* before;
      before = after->prev;
      Node* temp = i.node_ptr;
      temp = new Node();
      temp->next = after;
      temp->prev = before;
      temp->datum = datum;
      if (before) {
          before->next = temp;
      }
      else {
          first = temp;
      }
      ++size_list;
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
