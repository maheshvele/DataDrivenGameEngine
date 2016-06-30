#pragma once
#include <cstdint>

namespace Library
{
	//! Templated class Vector
	/*!
	The vector class stores elements of type T in a contiguous block of memory. It has
	functionality for pushing to the back, popping from the back, checking the size, front
	and back elements, finding elements by reference or by index, and clearing the container.
	It also contains an implementation of an iterator, used to navigate through the elements
	of the vector. Along with this is functionality to acquire iterators referencing the beginning
	or end of the vector, and the functionality to acquire an iterator referencing a specific element.
	Using these iterators, funcionality to remove an element or range of elements based on supplied iterators
	has been implemented.
	*/

	template <typename T>
	class Vector
	{
	public:
		
		//! Iterator class
		/*!
		This class implements an iterator used by the Vector class to navigate through the data.
		The class itself contains definitions for the assignment operator, comparison operator,
		not-equal operator, incrment operator (both prefix and postfix), and the dereference operator.
		*/

		class Iterator
		{
			friend class Vector;
		public:

			/**
			Defualt constructor
			*/
			Iterator();

			/**
			Constructor for an iterator pointing at some existing data
			*/
			Iterator(unsigned int index, const Vector* owner);

			/**
			Copy constructor
			*/
			Iterator(const Iterator& rhs);

			/**
			Assignment operator
			*/
			Iterator& operator=(const Iterator& rhs);
			
			/**
			Comparison operator

			Checks equality. The given iterator must have the same data and owner values
			*/
			bool operator==(const Iterator& rhs) const;

			/**
			Not-equal operator
			*/
			bool operator!=(const Iterator& rhs) const;

			/**
			Prefix increment operator
			*/
			Iterator& operator++();

			/**
			Postfix increment operator
			*/
			Iterator operator++(int);

			/**
			Dereference operator
			*/
			T& operator*() const;


		private:
			unsigned int mIndex;
			const Vector* mOwner;
		};

	public:
		/**
		Default constructor

		Initialize list  to be empty
		*/
		Vector();

		/**
		Default destructor

		Clears the list using Clear()
		*/
		~Vector();

		/**
		Copy constructor

		@param rhs The vector whose values we want to copy
		*/
		Vector(Vector& rhs);

		/**
		Bracket operator

		Gets a reference to the item at the given index. Throws an exception of an index
		that is out of bounds is passed in.

		@param index the index in the vector of the item we want to retrieve
		@return returns the item at the given index
		@exception throws an exception if the supplied index is greater than size
		*/
		T& operator[](const unsigned int index);

		/**
		Bracket operator (const version)

		Gets a reference to the item at the given index. Throws an exception of an index
		that is out of bounds is passed in.

		@param index the index in the vector of the item we want to retrieve
		@return returns the item at the given index
		@exception throws an exception if the supplied index is greater than size
		*/
		T& operator[](const unsigned int index) const;

		/**
		Remove the last item of the vector

		The removal of the final element is done by simply decrementing the size. No memory
		is freed, as we need to maintain contiguous memory.
		*/
		void PopBack();

		/**
		Function checks to see if the vector contains anything

		Checeks the size of of the vector to see if it is empty

		@return True if size > 0. False otherwise
		*/
		bool IsEmpty();

		/**
		Function gets the front value of the vector

		Gets the elemnt at the index of 0.

		@return The first element of the vector
		*/
		T& Front();

		/**
		Function gets the front value of the vector

		Gets the elemnt at the index of 0.

		@return A reference to the first element of the vector
		*/
		T& Front() const;

		/**
		Function gets the back value of the vector

		Gets the element at the index of (size - 1)

		@return A reference to the last element of the vector
		*/
		T& Back();

		/**
		Function gets the back value of the vector

		Gets the element at the index of (size - 1)

		@return A reference to the last element of the vector
		*/
		T& Back() const;

		/**
		Function gets the number of elements in the vector

		Get the size value of the vector

		@return the number of  elements in the vector
		*/
		unsigned int Size() const;

		/**
		Get an iterator pointing at the start

		Get an iterator pointing at the first element

		@return an iterator pointing at the first element
		*/
		Iterator begin() const;

		/**
		Get an iterator  pointing indicating 'not in the list'

		Gets an iterator with nullptrs

		@return an iterator with nullptrs
		*/
		Iterator end() const;

		/**
		Function appends an element to the end of the vector

		Adds an element to index [size] and then increases the size value by one.
		If (size + 1) would be greater than the capcity of the list, Reserve() is 
		called with the value (size + 1) * 2

		@param the value to be pushed onto the vector
		*/
		Iterator PushBack(T& newValue);

		/**
		Assignment operator

		Does a deep copy of the vector on the right hand side. If the rhs is a the same
		as the vector (ie. myVector = myVector), this operation is skipped.

		@param rhs The vector whose values we want to copy
		*/
		Vector& operator=(Vector& rhs);

		/**
		Get a reference to the item at the given index

		Reteruns a reference to the value found at the given index
		
		@return a reference to a T value at the given index
		@param the index we want to get the value from
		@exception throws an exception if our index is out of bounds
		*/
		T& At(const unsigned int index);

		/**
		Function allocates memory up to a new capacity

		Allocates memory for a new capacity of items.

		@param the number of items we want  to reserve memory for
		@exception throws an exception if we try to reserve room for less than  we currently have
		*/
		void Reserve(const unsigned int capacity);

		/**
		Get an iterator pointing at the  given item

		Searches through the list for the given item. If the item does not exist
		in the list, we get end()

		@param item the item being searched for
		@return an iterator pointing to the item we are searching for
		*/
		Iterator Find(const T& item);

		/**
		Empty the list

		Deletes the buffer and sets the size to zero
		*/
		void Clear();

		/**
		Remove an element in the list that is pointed to by a given iterator

		@param target an iterator referencing the index of the item to be removed
		@exception thros an exception if the target is not owned by this vector, or its index is outside of the current size
		*/
		void Remove(const Iterator& target);

		/**
		Remove an element by index

		@param index the index of the item to remove
		@exception throw an exception if the target is out of bounds
		*/
		void Remove(const std::uint32_t index);

		/**
		Overload for remove that removes all elements between two given iterators

		@param startTarget iterator referencing the index of the item to start removal from
		@param endTarget iterator referencing the index of the item to end removal at
		@exception thros an exception if either target is not owned by this vector, or either index is outside of the current size
		*/
		void Remove(const Iterator& startTarget, const Iterator& endTarget);


		/** Member variable that tracks the maximum number of elements in the Vector*/
		unsigned int mCapacity;

	private:
		/** Member variable that stores the values in contiguous memory*/
		T* mBuffer;

		/** Member variable that tracks the current number of elements in the Vector*/
		unsigned int mSize;

		

	};


}

#include "Vector.inl"