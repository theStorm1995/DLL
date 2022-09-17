#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP

// Name: Nathan Storm 
// CWID: 885905158
// Email: nathanstorm95@csu.fullerton.edu

/**
 * TODO: Implement DoublyLinkedList, its Node, and its Iterator!
 * 
 * I've left some methods filled out for you,
 * 	and stubbed out some structure, to reduce difficulty.
 * 
 * You may add or remove methods as you see fit,
 * 	as long as you can still pass all unit tests.
 * Although, it may be more difficult to do so. Your choice!
 * 
 * Notice we're inside a namespace here.
 * The DLL is inside a namespace called DoublyLinkedList,
 * 	which is itself inside a namespace called CPSC131
 * This means, if you'd like to play around with your class later,
 * 	you'll need to access it like so:
 * ::CPSC131::DoublyLinkedList::DoublyLinkedList<int> list;
 * 
 * Look into main.cpp and CPP_Tests.cpp for examples of using
 * 	the DLL and your BookStore. But don't worry too much, as you
 * 	only need to implement these classes
 * (main and tests are already done for you)
 */


//
#include <iostream>
#include <stdlib.h>
#include <stdexcept>


/**
 * Namespace for our classroom !
 */
namespace CPSC131
{
	/**
	 * Namespace to hold all things related to our DLL
	 */
	namespace DoublyLinkedList
	{
		/**
		 * Node class, which our DLL will use
		 * 
		 * The Professor realizes he could have made this an inline class (like the Iterator),
		 * but he is lazy.
		 */
		template <class T>
		class Node
		{
			public:
				
				/// CTORS: YOUR WELCOME
				Node() : prev_(nullptr), next_(nullptr) {}
				Node(T element) : element_(element), prev_(nullptr), next_(nullptr) {}
				Node(T element, Node* prev, Node* next) : element_(element), prev_(prev), next_(next) {}
				
				/// Set the pointer to the previous element
				void setPrevious(Node* prev) {
					prev_ = prev;
				}
				
				/// Set the pointer to the previous element
				void setPrev(Node* prev) {
					setPrevious(prev);
				}
				
				/// Get a pointer to the previous element
				Node* getPrevious() {
					return getPrev();
				}
				
				/// Get a pointer to the previous element
				Node* getPrev() {
					return prev_;
				}
				
				/// Set the pointer to the next node
				void setNext(Node* next) {
					next_ = next;
				}
				
				/// Get a pointer to the next node
				Node* getNext() {
					return next_;
				}
				
				/// Set the element this node holds
				void setElement(T element) {
					element_ = element;
				}
				
				/// Get the element this node holds
				T& getElement() {
					return element_;
				}
				
				/// Return a reference to the element
				T& operator*() {
					return getElement();
				}
				
			private:
				T element_;
				Node* prev_;
				Node* next_;
		};
		
		/**
		 * Implement our DoublyLinkedList class !
		 */
		template <class T>
		class DoublyLinkedList
		{
			public:
				
				/**
				 * Nested Iterator class.
				 * This allows user code to refer to the Iterator's type as:
				 * 
				 * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
				 * 
				 * (as opposed to specifying the template argument two times)
				 */
				class Iterator
				{
					public:
						
						///	Constructor taking a head and tail pointer; YOUR WELCOME
						Iterator(Node<T>* head, Node<T>* tail) : head_(head), tail_(tail)
						{
							this->cursor_ = this->end();
						}
						
						///	Constructor taking a head, tail, and cursor pointer; YOUR WELCOME
						Iterator(Node<T>* head, Node<T>* tail, Node<T>* cursor) : head_(head), tail_(tail), cursor_(cursor) {}
						
						///	Get a pointer to the head node, or end() if this list is empty
						Node<T>* begin()
						{
 							if(head_->getNext() == tail_) {
								return this->end();
							}
							else {
								return head_;
							} 
						}
						
						///	Get a node pointer representing "end" (aka "depleted"). Probably want to just use nullptr.
						Node<T>* end()
						{
 							return tail_; 
						}
						
						///	Get the node this iterator is currently pointing to
						Node<T>* getCursor()
						{
 							return cursor_; 
						}
						
						/**
						 * Assignment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator=(const Iterator& other)
						{
 							this->head_ = other.head_;
							this->tail_ = other.tail_;
							this->cursor_ = other.cursor_;

							return *this; 
						}
						
						///	Comparison operator
						bool operator==(const Iterator& other)
						{
							// Check if the pointers of 2 iterator objects are pointing the the same thing
 							if((other.tail_ == this->tail_) && (other.head_ == this->head_) && (other.cursor_ == this->cursor_)) {
								return true;
							}
							return false; 
						}

						///	Inequality comparison operator
						bool operator!=(const Iterator& other)
						{
							// Returns the inverse of the comparison operator
 							if(operator==(other)) {
								return false;
							}
							return true; 
						}
						
						/**
						 * Prefix increment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator++()
						{
							if(this->cursor_ == this->end()) {
								return *this;
							}
							this->cursor_ = this->cursor_->getNext();
							return *this; 
						}
						
						/**
						 * Postfix increment
						 * Return a copy of this Iterator, BEFORE it was modified
						 */
						Iterator operator++(int)
						{
							DoublyLinkedList::Iterator temp(this->head_, this->tail_, this->cursor_);
							this->operator++();
							return temp;
						}
						
						/**
						 * Prefix decrement operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator--()
						{
							if(this->cursor_ == this->end()) {
								return *this;
							}
							this->cursor_ = this->cursor_->getPrev();
							return *this; 
						}
						
						/**
						 * Postfix decrement operator
						 * Return a copy of this Iterator BEFORE it was modified
						 */
						Iterator operator--(int)
						{
							DoublyLinkedList::Iterator temp(this->head_, this->tail_, this->cursor_);
							*this->operator--();
							return temp;
						}
						
						/**
						 * AdditionAssignment operator
						 * Return a copy of the current iterator, after modification
						*/
						Iterator operator +=(size_t add)
						{
 							for(size_t i = 0; i < add; i++) {
								this->operator++();
							}
							return *this; 
						}
						/**
						 * SubtractionAssignment operator
						 * Return a copy of the current iterator, after modification
						 */
						Iterator operator -=(size_t add)
						{
 							for(size_t i = 0; i < add; i++) {
								this->operator--();
							}
							return *this; 
						}
						
						/**
						 * AdditionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator +=(int add)
						{
  							if(add >= 0) {
								for(int i = 0; i < add; i++) {
									this->operator++();
								}
							}
							else {
								add = abs(add);
								for(int i = 0; i < add; i++) {
									this->operator--();
								}
							}
							return *this;  
						}
						
						/**
						 * SubtractionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator -=(int subtract)
						{
  							if(subtract >= 0) {
								for(int i = 0; i < subtract; i++) {
								this->operator--();
								}
							}
							else {
								subtract = abs(subtract);
								for(int i = 0; i < subtract; i++) {
								this->operator++();
								}
							}
							return *this;  
						}
						
						/**
						 * Dereference operator returns a reference to the ELEMENT contained with the current node
						 */
						T& operator*()
						{
							return this->cursor_->getElement();
						}
					
					private:
						
						/// Pointer to the head node
						Node<T>* head_ = nullptr;
						
						/// Pointer to the tail node
						Node<T>* tail_ = nullptr;
						
						/**
						 * Pointer to the cursor node.
						 * This is only one way of letting the iterator traverse the linked list.
						 * You can change to a different method if you wish (and can still pass unit tests)
						 */
						Node<T>* cursor_ = nullptr;
					
					/// YOUR WELCOME
					friend class DoublyLinkedList;
				};
				
				/// Your welcome
				DoublyLinkedList() {
					// Create the 2 sentinal nodes
					size_ = 0;
					head_ = new Node<T>;
					tail_ = new Node<T>;

					// Make them point to each other
					head_->setNext(tail_);
					tail_->setPrev(head_);
				}
				
				///	Copy Constructor
				DoublyLinkedList(DoublyLinkedList& other)
				{
					// Create 2 sentinal nodes
  					this->size_ = 0;
					this->head_ = new Node<T>;
					this->tail_ = new Node<T>;

					// Make them point to each other
					this->head_->setNext(tail_);
					this->tail_->setPrev(head_);  

					// Iterate through other list and add each node into "this" list
					for(auto itr = other.begin(); itr != other.end(); itr++) {
						this->push_back(*itr);
					}
				}
				
				/// DTOR: Your welcome
				~DoublyLinkedList()
				{
					// Make sure we only clear if its not empty
					if(!(this->empty())) {
						this->clear();
					}
					
					// Make sure we dont deallocate memory for sentinals twice
					if(head_->getNext() == tail_) {
						// Set pointers = to null pointers
						head_->setNext(nullptr);
						tail_->setPrev(nullptr);

						// Deallocate memory and set pointers to null pointers
						delete head_;
						delete tail_;
						head_ = nullptr;
						tail_ = nullptr;
					}
				}
				
				/**
				 * Clear the list and assign the same value, count times.
				 * If count was 5, T was int, and value was 3,
				 * 	we'd end up with a list like {3, 3, 3, 3, 3}
				 */
				void assign(size_t count, const T& value)
				{
					// Clear the list
 					this->clear();

					// Run a loop count times and push the value to the front
					for(size_t i = 0; i < count; i++) {
						push_front(value);
					} 
				}
				
				/**
				 * Clear the list and assign values from another list.
				 * The 'first' iterator points to the first item copied from the other list.
				 * The 'last' iterator points to the last item copied from the other list.
				 * 
				 * Example:
				 * 	Suppose we have a source list like {8, 4, 3, 2, 7, 1}
				 * 	Suppose first points to the 4
				 *	Suppose last points to the 7
				 * 	We should end up with our list becoming: {4, 3, 2, 7}
				 *
				 * If the user code sends out-of-order iterators,
				 * 	just copy from 'first' to the end of the source list
				 * Example: first=7, last=4 from the list above would give us:
				 * 	{7, 1}
				 */
				void assign(Iterator first, Iterator last)
				{
					while(first != last || first == nullptr) {
						push_back(*first);
						first++;
					}
				}
				
				/// Return a pointer to the head node, if any
				Node<T>* head() {
					return head_;
				}
				
				/// Return a pointer to the tail node, if any
				Node<T>* tail() {
					return tail_;
				}
				
				/**
				 * Return an iterator that points to the head of our list
				 */
				Iterator begin()
				{
					DoublyLinkedList<T>::Iterator itr(head_, tail_, head_->getNext());
					return itr;
				}
				
				/**
				 * Return an iterator that points to the last element (tail) of our list
				 */
				Iterator last()
				{
					DoublyLinkedList::Iterator itr(head_, tail_, tail_->getPrev());
					return itr;
				}
				
				/**
				 * Should return an iterator that represents being past the end of our nodes,
				 * or just that we are finished.
				 * You can make this a nullptr or use some other scheme of your choosing,
				 * 	as long as it works with the logic of the rest of your implementations.
				 */
				Iterator end()
				{
					DoublyLinkedList<T>::Iterator itr(head_, tail_, tail_);
					return itr;
				}
				
				/**
				 * Returns true if our list is empty
				 */
				bool empty() const
				{
					return (size_ == 0);
				}
				
				/**
				 * Returns the current size of the list
				 * Should finish in constant time!
				 * (keep track of the size elsewhere)
				 */
				size_t size() const
				{
					return size_;
				}
				
				/**
				 * Clears our entire list, making it empty
				 * Remember: All removal operations should be memory-leak free.
				 */
				void clear()
				{
 					while(size_ != 0) {
						pop_front();
					} 
				}
				
				/**
				 * Insert an element after the node pointed to by the pos Iterator
				 * 
				 * If the list is currently empty,
				 * 	ignore the iterator and just make the new node at the head/tail (list of length 1).
				 * 
				 * If the incoming iterator is this->end(), insert the element at the tail
				 * 
				 * Should return an iterator that points to the newly added node
				 * 
				 * To avoid repeated code, it might be a good idea to have other methods
				 * 	rely on this one.
				 */
				Iterator insert_after(Iterator pos, const T& value)
				{
  					// Create pointers that point to the prev and next nodes address
					Node<T>* node_prev = pos.getCursor();
					Node<T>* node_next = pos.getCursor()->getNext();

					// If the list is empty set prev and next to head and tail
					if(empty()) {
						node_prev = head_;
						node_next = tail_;
					}

					// If the iterator is at the end then set prev and next to insert at end
					if(pos == this->end()) 
					{
						node_prev = tail_->getPrev();
						node_next = tail_;
					}

					// Allocate memorey for new node 
					Node<T>* new_node = new Node<T>;

					// Make new node point to nodes before and after it
					// Also make the new nodes element = to value
					// Increase the list size by 1
					new_node->setNext(node_next);
					new_node->setPrev(node_prev);
					new_node->setElement(value);
					node_prev->setNext(new_node);
					node_next->setPrev(new_node);
					size_++;

					// 
					node_prev = nullptr;
					node_next = nullptr;

					// Make the iterator cursor point to the new node
					pos.cursor_ = new_node;
					return pos; 
				} 
				
				/**
				 * Insert a new element after the index pos.
				 * Should work with an empty list.
				 * 
				 * Should return an iterator pointing to the newly created node
				 * 
				 * To reduce repeated code, you may want to simply find
				 * 	an iterator to the node at the pos index, then
				 * 	send it to the other overload of this method.
				*/
				Iterator insert_after(size_t pos, const T& value)
				{
					DoublyLinkedList::Iterator itr(head_, tail_, head_);

					// Make the iterators cursor point to the index position
					for(size_t i = 0; i <= pos; i++) {
						itr++;
					}

					// Insert a node after the index pos
					return insert_after(itr, value);
				}
				
				/**
				 * Erase the node pointed to by the Iterator's cursor.
				 * 
				 * If the 'pos' iterator does not point to a valid node,
				 * 	throw an std::range_error
				 * 
				 * Return an iterator to the node AFTER the one we erased,
				 * 	or this->end() if we just erased the tail
				 */
				Iterator erase(Iterator pos)
				{
					// Make sure the iterators cursor is actually pointing to a node
 					if(pos.getCursor() == nullptr) {
						throw std::range_error("Node does not exist!");
					} 

					// Set pointers = to the prev and next nodes
					Node<T>* prev = pos.getCursor()->getPrev();
					Node<T>* next = pos.getCursor()->getNext();
					DoublyLinkedList::Iterator temp_pos(head_, tail_, head_);
					temp_pos.cursor_ = pos.getCursor()->getNext();

					// Make the prev and next nodes point to each other
					prev->setNext(next);
					next->setPrev(prev);

					// Set the current nodes pointers = to null pointers
					pos.getCursor()->setNext(nullptr);
					pos.getCursor()->setPrev(nullptr);

					// Deallocate the current node and decrease the list size by 1
					delete pos.getCursor();
					size_--;

					// 
					if(next->getNext() == tail_) {
						return this->end();
					}
					else {
						pos = temp_pos;
						return pos;
					}
				}
				
				/**
				 * Add an element just after the one pointed to by the 'pos' iterator
				 * 
				 * Should return an iterator pointing to the newly created node
				 */
				Iterator push_after(Iterator pos, const T& value)
				{
					return insert_after(pos, value);
				}
				
				/**
				 * Add a new element to the front of our list.
				 */
				void push_front(const T& value)
				{
					DoublyLinkedList::Iterator itr(head_, tail_, head_);
					insert_after(itr, value);
				}
				
				/**
				 * Add an element to the end of this list.
				 * 
				 * Should return an iterator pointing to the newly created node.
				 */
				Iterator push_back(const T& value)
				{
					DoublyLinkedList::Iterator itr(head_, tail_, tail_->getPrev());
					return insert_after(itr, value);
				}
				
				/**
				 * Remove the node at the front of our list
				 * 
				 * Should throw an exception if our list is empty
				 */
				void pop_front()
				{
					// Make sure list isn't empty
					if(empty()) {
						throw std::length_error("List is empty :( no pop");
					}

					// Make itr point to front of list and erase that node
					DoublyLinkedList::Iterator itr(head_, tail_, head_->getNext());
					erase(itr); 
				}
				
				/**
				 * Return a reference to the element at the front.
				 * 
				 * Throw an exception if the list is empty
				 */
				T& front()
				{
					if(empty()) {
						throw std::range_error("List is empty");
					}
					return head_->getNext()->getElement();
				}
				
				/**
				 * Return a reference to the element at the back.
				 * 
				 * Throw an exception if the list is empty
				 */
				T& back()
				{
					if(empty()) {
						throw std::range_error("List is empty");
					}
					return tail_->getPrev()->getElement();
				}
				
				/**
				 * Return the element at an index
				 * 
				 * Should throw a range_error is out of bounds
				 */
				T& at(size_t index)
				{
					// Check if the index is out of bounds
					if(index > size_ - 1) {
						throw std::range_error("Index out of range.");
					}

					// Make an iterator point to the index pos
					DoublyLinkedList::Iterator itr(head_, tail_, head_);
					for(size_t i = 0; i <= index; i++) {
						itr++;
					}
					return *itr; 
				}
				
				/**
				 * Reverse the current list
				 * 
				 * It might be easy to consider the following:
				 * - Create a temp empty list
				 * - Iterate through the current list
				 * - For each item in the current list, push to the FRONT (not back)
				 * - Assign the current list to the temp list
				 * - Discard the temp list
				 */
				void reverse()
				{
					// Make a temp list 
					DoublyLinkedList<T> temp;

					// Iterate through the current list and push each node to the front of temp list
					for(auto itr = this->begin(); itr != this->end(); itr++) {
						temp.push_front(*itr);
					}

					// Make the current list = temp(reversed list)
					*this = temp;
					temp.clear();
				}
				
				/**
				 * I bet you're happy I'm not making you do this.
				 * No tests will be run against this function,
				 * 	but feel free to try it out, as a challenge!
				 * 
				 * If I were doing this and didn't care too much for efficiency,
				 * 	I would probably create an extra helper function to swap two
				 * 	positions in the current list.
				 * Then I would simply sweep through the list bubble-sort style.
				 * Perhaps selection sort.
				 * 
				 * If you want a huge challenge, try implementing quicksort.
				 * 
				 * (but again, don't worry about this method; it will not be tested)
				 */
				void sort()
				{
					
				}
				
				/**
				 * Assignment operator
				 * 
				 * Clear this list and fill it with the others' values
				 * (by value, not by reference)
				 * 
				 * Return a reference to this list
				 */
				DoublyLinkedList<T>& operator =(DoublyLinkedList<T>& other)
				{
					// Clear the current list
 					this->clear();

					// Push back each element of the other list into the current list
					for(auto itr = other.begin(); itr != other.end(); itr++) {
						this->push_back(*itr);
					}
					return *this; 
				}
				
				/**
				 * Return true if the lists are "equal"
				 * 
				 * "Equal" here is defined as:
				 * - Same size
				 * - Elements at the same indexes would return true for their own comparison operators
				 * 
				 * In other words: "They contain all the same values"
				 * (no need to be references to each other)
				 */
				bool operator ==(DoublyLinkedList<T>& other)
				{	
					auto itr_other = other.begin();

					// Iterate through the current list 
					for(auto itr = this->begin(); itr != this->end(); itr++) {
						// Check if this element is equal to other element
						if(*itr != *itr_other) {
							return false;
						}
						itr_other++;
					}

					// See if this size is = to other size
					if(this->size_ == other.size()) {
						return true;
					}
					else {
						return false;
					}
				}
				
				/**
				 * Return true if the lists are "not equal"
				 * 
				 * See the operator== stub for definition of "equal"
				 * 
				 * Probably want to avoid repeated code by relying on the other operator
				 */
				bool operator !=(DoublyLinkedList<T>& other)
				{
					if(this->operator==(other)) {
						return false;
					}
					else {
						return true;
					}
				}
				
			private:
				Node<T>* head_ = nullptr;
				Node<T>* tail_ = nullptr;
				size_t size_ = 0;
		};
	}
}

#endif















































/// Yes, I'm aware it's spelled you're*
