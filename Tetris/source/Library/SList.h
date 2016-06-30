#pragma once
#include <cstdint>

namespace Library
{
	//! Templated class SList
	/*!
		This class is an implementation of a singly linked list for generic data types.
		It contains an internal private Node class used to store the data and the connections
		of the list. The class supports functionality for pushing to the front of the list,
		pushing to the back of the list, popping from the top of the list, checking the front and back,
		clearing the list, and checking the number of items currently stored in the list. It also has
		overloaded the copy constructor and the assignment operator.
	*/

	template <typename T>
	class  SList
	{
	private:
		//! Private internal node class
		/*!
			This class is an implementation of the nodes that are used in the linked list. Each contains
			a data member and a pointer to the next node in the list. All of these are private, and are such
			accessed via public getter and setter functions.
		*/
		class Node
		{
		public:
			/**
			Constructor for a node with given data and next value
			*/
			Node(const T& data, Node* next = nullptr);

			/**
			Getter function for the data of the node
			*/
			T& GetData();

			/**
			Getter function for the next pointer of the node
			*/
			Node* GetNext();

			/**
			Setter function for the next pointer of the node
			*/
			void SetNext(Node* newNext);

		private: 
			Node(const  Node& rhs) = delete;
			Node& operator = (const Node& rhs) = delete;

			T mData;
			Node* mNext;
		};

	public:

		//! Iterator class
		/*!
		This class implements an iterator used by the SList class to navigate through the list.
		The class itself contains definitions for the assignment operator, comparison operator,
		not-equal operator, incrment operator (both prefix and postfix), and the dereference operator.
		*/

		class Iterator
		{
			friend class SList;
		public:
			/**
			Constructor for Iterator with given node and owner
			*/
			Iterator(Node* node = nullptr, SList* owner = nullptr);

			/**
			Copy constructor
			*/
			Iterator(const Iterator& rhs);

			/**
			Assignment operator

			Copies the values of another iterator
			*/
			Iterator& operator=(const Iterator& rhs);

			/**
			Comparison operator

			Checks the equality of two iterators. For this to return true, both the owner of the
			iterator and the node the iterators are pointing at have to match.
			*/
			bool operator==(const Iterator& rhs) const;

			/**
			Not-equal operator

			Checks for the opposite conditions of the comparison operator, returning true only when
			either the owner or the node of the iterators don't match
			*/
			bool operator!=(const Iterator& rhs) const;

			/**
			Prefix increment operator

			Sets the referenced node to the next node in the list. If the node has already passed the 
			final node of the list, then no change occurs.
			*/
			Iterator& operator++();

			/**
			Postfix increment operator

			Works similar to the prefix operator, but it also returns what the values of the iterator
			were before the increment
			*/
			Iterator operator++(int);

			/**
			Dereference operator

			Gets a reference to the data in the node that is being pointed at by the iterator

			@exception throws an exception if the iterator's node variable is currently  a  null pointer
			*/
			T& operator*() const;
		
		private:

			/**
			The node that the iterator is currently referencing
			*/
			Node* mNode;

			/**
			The SList containing the node that the iterator is currently referencing
			*/
			SList* mOwner;
		};

		/**
		Default constructor
		*/
		SList();

		/**
		Default destructor
		*/
		~SList();

		/**
		The copy constructor. Creates the SList with the values of another SList

		The copy constructor acquires a deep copy of the provided SList 'rhs' by
		using the assignment operator.

		@param rhs a const reference to the SList that is to be copied
		*/
		SList(const SList& rhs);

		/**
		The assignment operator. Copies the values of another SList

		The assignment operator begins by clearing the current list so we can take the new values
		The operator then calls the deepCopy function to get all of the values
		of the provided SLIst 'rhs' and copy them into this SList.

		@param rhs a const reference to the SList that is to be copied
		@return returns a reference to the list which would now contain the data from rhs
		*/
		SList& operator=(const SList& rhs);
		
		/** 
		PushFront pushes the data to a new node at the front of the list

		This function creates a new node with the data provided and adds it to the front of the list.
		The old front of the list is set to the next pointer of the new front, and the front pointer of
		the list is set to the newly constructed front node. After this, the size is also incremented

		@param data the data used to construct the new node
		*/
		void PushFront(const T& data);

		/**
		PopFront pops a node from the front of the list

		This function first sets the front pointer of the list to refer to the new front of the list,
		which is the current second node of the list. This is accessed via the next pointer of the current
		front of the list. After this has been established, the old front node is deleted. 
		*/
		void PopFront();

		/**
		PushBack pushes data to a new node at the back of the list

		This function creates a new node with the data provided and adds it to the back of the list.
		The old back of the list has its next pointer set to this new node, and the back pointer of 
		the list is set to the newly constructed back node. After this, the size is also incremented

		@param data the data used to construct the new node
		*/
		Iterator PushBack(T data);
		
		/**
		Front accesses a reference to the data stored at the front node

		This function checks the front pointer of the SList and returns a reference to the data stored
		in the current head of the list.

		@return a reference to the data contained by the front node of the list
		@exception throws an exception when called with an empty list
		*/
		T& Front() const;

		/**
		Back accesses a reference to the data stored at the back node

		This function checks the back pointer of the SList and returns a reference to the data stored
		in the current tail of the list.

		@return a reference to the data contained by the back node of the list
		@exception throws an exception when called with an empty list
		*/
		T& Back() const;

		/**
		IsEmpty checks to see if the list is empty or not

		This function checks to see if the size member of the list is equal to zero

		@return Return true if the list is empty. Return false if the list is not empty
		*/
		bool IsEmpty() const;

		/**
		Removes all nodes from the list using PopFront()

		This function checks the size of the list and continuously calls PopFront() until
		the list is empty. 
		*/
		void Clear();
		
		/**
		Returns the current size of the list

		This function checks how many nodes are in the list by accessing the size member variable

		@return Returns a std::uint32_t with the values of the size of the list
		*/
		std::uint32_t Size() const;

		/**
		Make a new iterator for the front of the list

		This function is used for initializing an iterator at the head of the SList

		@return Returns an SList::Iterator pointing to the head of the list 
		*/
		Iterator begin() const;

		/**
		Make a new iterator for the back of the list

		This function would be used to initialize an iterator pointing past the end of the list.
		Due to singly linked lists not dealing with contiguous memory, however, the mNode value
		is simply set to nullptr

		@return Returns an SList::Iterator pointing past the end of the list.
		*/
		Iterator end() const;

		/**
		Append the given item after the given iterator

		This function first checks if the iterator passed in is owned by this list. If it is not, then
		we throw an exception rather than exiting without doing anything. Next, the function checks to see if
		the iterator parameter is pointing passed the end of the list. If it is, the value is pushed to
		the back of the list. Finally, we walk the list to confirm that the iterator is pointing to a node
		that is still in the list. If it does not, the value is pushed to the back. Otherwise, it is inserted
		after the node referenced by the given parameter.

		@param item the item of type T to be appended after the given iterator
		@param iterator the iterator pointing to the point of insertion
		@exception throws an exception if the iterator is not owned by the list it was called with
		*/
		void InsertAfter(const T& item, const Iterator& insertionIterator);

		/**
		Get an iterator pointing to the given item
		
		This function walks the list, seraching for a node containing the value passed in. If one is found,
		an iterator pointing to it is returned. If not, End() is returned.

		@param value the value that we search to find an iterator for 
		@return an iterator pointing to the node containing the value parameter
		*/
		Iterator Find(const T& value) const;

		/**
		Remove item associated with given data and maintain list integrity

		This function begins by checking to see if the value is at the head of the list. If so, the function
		simply pops it off the front. Otherwise the list is walked until the value is found. If no such value
		exists in the list, the function exits without editing the list. Otherwise the node whose next pointer
		corresponds to the removed node is set to point to the node after it, and the node itself is removed from
		the list and deleted. 

		@param value the value of the data stored in the node that we will remove
		*/
		void Remove(const T& value);


	private:
		/** Member variable that is a pointer to the start of the list*/
		Node* mFront;

		/** Member variable that is a pointer to the end of the list*/
		Node* mBack;

		/** Member variable that keeps track of how many nodes are in the list*/
		std::uint32_t mSize;
	};
}


#include "SList.inl"