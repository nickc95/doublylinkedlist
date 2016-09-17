// Description: Implementation of a doubly linked list template class

#ifdef _LINKEDLIST_H_

using namespace std;

//#include "linkedlist.h"

// helper function for deep copy
// Used by copy constructor and operator=
template <typename T>
void LinkedList<T>::CopyList(const LinkedList& ll){

	Node<T>* curr = ll.front;
	int index = 0;

	while (curr != NULL){
		InsertAt(curr->data, index);
		index++;
		curr = curr->next;
	}
	
}

// helper function for deep delete
// Used by destructor and copy/assignment
template <typename T>
void LinkedList<T>::DeleteList(){
	Node<T>* curr = front;

	while(curr != NULL){ // traverse through list
		curr = curr->next;
		delete(front);
		front = curr;
	}
}

//Default constructor
template <typename T>
LinkedList<T>::LinkedList(){

	front = NULL;
	back = NULL;
	size = 0;
}

// Copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& ll){

	front = NULL;
	back = NULL;
	size = 0;

	CopyList(ll);
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList(){
	DeleteList();
}

// MUTATORS

// Inserts an item at the front of the list
// POST:  List contains item at position 0
// PARAM: item = item to be inserted
template <typename T>
void LinkedList<T>::InsertFront(T item){
	Node<T>* newNode = new Node<T>(item);
	newNode->next = NULL;
	newNode->prev = NULL;


	if(size == 0){ // newly initialised linkedlist
		front = newNode;
		back = newNode;
		size++;
	} else {
		newNode->next = front;
		front->prev = newNode;
		front = newNode;
		size++;
	}
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
template <typename T>
void LinkedList<T>::InsertBack(T item){
	Node<T>* newNode = new Node<T>(item);
	newNode->next = NULL;
	newNode->prev = NULL;

	Node<T>* curr = front;

	if(size == 0){ // newly initialised linkedlist
		front = newNode;
		back = newNode;
		size++;
	} else {
		while (curr != NULL){ // traverse
			if (curr->next == NULL){ // last node in list
				curr->next = newNode;
				newNode->prev = curr;
				back = newNode;
				curr = NULL;
				size++;
			} else {
				curr = curr->next;
			}
		}

	}
}

// Inserts an item in position p (0-indexed)
// Throws exception for invalid index
// PRE:   0 <= p <= size
// POST:  List contains item at position p
// PARAM: item = item to be inserted, p = position where item will be inserted
template <typename T>
void LinkedList<T>::InsertAt(T item, int p){
	int index = 0;

	Node<T>* newNode = new Node<T>(item);
	newNode->next = NULL;
	newNode->prev = NULL;

	Node<T>* curr = front;

	if (0 <= p && p <= size) { // is index in range? if not, throws exception

		while(index < p){ // use index to bring curr pointer to position p
			if (curr->next == NULL){
				index++;
			} else {
				curr = curr->next;
				index++;
			}
		}

		// 1 master case: is the ll freshly initialised?
		// 3 more cases required:
		// inserted node is not last or first
		// inserted node becomes first
		// inserted node becomes last

		if (size == 0){
			front = newNode;
			back = newNode;
			size++;

		} else {

			if (p < size && p != 0) { // inserted node is not last or first
				newNode->next = curr;
				newNode->prev = curr->prev;
				curr->prev->next = newNode;
				curr->prev = newNode;
				size++;
			}
			else if (p == size) { // inserted node is becoming last
				curr->next = newNode;
				newNode->prev = curr;
				back = newNode;
				size++;
			}
			else { // inserted node is becoming first (p = 0)
				newNode->next = curr;
				curr->prev = newNode;
				front = newNode;
				size++;
			}
			
		}

	} else {
		throw std::out_of_range("LinkedList<T>::InsertAt - Index out of range");
	}

}

// Removes and returns an item from position p (0-indexed)
// Throws exception if list is empty or index invalid
// PRE:   0 <= p < size
// POST:  Item is removed from list
// PARAM: p = position from where item will be removed
template <typename T>
T LinkedList<T>::RemoveAt(int p){

	int index = 0;
	T item;
	Node<T>* curr = front;
	
	if (0 <= p && p < size){

		while (index < p) { // traverse list until curr is at position p
			curr = curr->next;
			index++;
		}

		if (size == 1){ // is node to be removed the only one in list
			front = NULL;
			back = NULL;
			size = 0;
			item = curr->data;
			DeleteList();

		} else {

			if(curr->next == NULL) {  // if node to be removed is last in list
				back = curr->prev;
				curr->prev->next = NULL;
				item = curr->data;
				delete curr;
				size--;

			} else if (curr->prev == NULL) { // if node to be removed is first in list
				front = curr->next;
				curr->next->prev = NULL;
				item = curr->data;
				delete curr;
				size--;

			} else { // node to be removed is between 2 normal nodes
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
				item = curr->data;
				delete curr;
				size--;
			
			}
		}

	} else {
		throw std::out_of_range("LinkedList<T>::RemoveAt - Index out of range");
	}

	return item;
}

// Appends the contents of the parameter list to the back of this list as a deep copy
// PRE:
// POST: List contains every element of ll appended to back, size is updated appropriately
template <typename T>
void LinkedList<T>::Append(const LinkedList& ll){
	Node<T>* temp = ll.front;
	int index = size; // deep copy takes place at back of list

	while (temp != NULL){
		InsertAt(temp->data, index);
		index++;
		temp = temp->next;
	}
}

// Removes duplicates from the list, preserving existing order of remaining items.
// The LAST occurrence of any duplicate (relative to the front of the list)
//   is the one which remains.
// Efficiency will not be a priority as long as the behaviour above is satisfied.
// PRE:   
// POST:  List contains no duplicates, front and back point to the appropriate nodes
// PARAM: 
template <typename T>
void LinkedList<T>::RemoveDuplicates(){
	Node<T>* pointer_A = front;
	Node<T>* pointer_B = front;
	Node<T>* temp;

	while (pointer_A != NULL) { // traverse list

		pointer_B = pointer_A; // no need to check values before pointer_A (already checked)

		while (pointer_B->next != NULL) { // check item against other items in list, excluding itself

			if (pointer_A->data == pointer_B->next->data){ // data is the same?

				if (pointer_B->next->next == NULL){ // check if data to be deleted is last in list
					back = pointer_B;
				}
				temp = pointer_B->next;
				pointer_B->next = pointer_B->next->next;
				size--;
				delete temp;
				
			} else {
				pointer_B = pointer_B->next;
			}
		}

		pointer_A = pointer_A->next; // increment pointer A
	}
}

// ACCESSORS

// Returns size of list
template <typename T>
int LinkedList<T>::Size() const {
	return size;
}

// Returns whether the list is empty
template <typename T>
bool LinkedList<T>::IsEmpty() const {
	return (size == 0);
}

// Returns existence of item
template <typename T>
bool LinkedList<T>::Contains(T item) const {

	Node<T>* curr = front;
	
	while (curr != NULL){
		if(item == curr->data){
			return true;
		}

		curr = curr->next;
	}
	return false;
}

// Returns item at index (0-indexed)
// Throws exception for invalid index
template <typename T>
T LinkedList<T>::ElementAt(int p) const {
	int index = 0;
	Node<T>* curr = front;
	
	if (0 <= p && p < size){
		while (index < p) {
			curr = curr->next;
			index++;
		}

		return curr->data;

	} else {
		throw std::out_of_range("LinkedList<T>::ElementAt - Index out of range");
	}
}

// OVERLOADED OPERATORS

// overloaded assignment operator
// must work in the following cases:
// list2 = list1 -> general case
// list2 = list2 -> should do nothing
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll) {

	if (!AreEquals(front, ll.front)){
		CopyList(ll);
	}
	
	return *this;
}

// assignment operator helper 
template <typename T>
bool LinkedList<T>::AreEquals(Node<T>* node_A, Node<T>* node_B) {
	while (node_A != NULL && node_B != NULL){

		if (node_A->data != node_B->data){ // check that nodes are equal
			return false;
		}

		node_A = node_A->next; // traverse both linked lists
		node_B = node_B->next;
	}

	return (node_A == NULL && node_B == NULL); // both lists have equal number of nodes
}



#endif


