#pragma once
#include <cstdint>
#include "SList.h"

namespace Library
{
	//! Templated class Stack
	/*!
		This class is an implementation of a stack for generic data types. Almost 
		all of its functionality comes from the SList class. The stack contains an
		SList member variable, which it uses to store and access all of the data.
		This class has functionality for pushing, popping, checking the top element,
		checking the number of elements, and clearing the stack.
	*/

	template <typename T>
	class Stack
	{
	public:
		/**
		Default constructor
		*/
		Stack();

		/**
		Destructor
		*/
		~Stack();

		/**
		Copy constructor

		@param rhs a reference to the Stack to be copied
		*/
		Stack(const Stack& rhs);

		/**
		Assignment operator

		@param rhs a reference to the Stack to be copied
		@return a reference to this stack with its newly copied values
		*/
		Stack& operator=(const Stack& rhs);

		/**
		Push

		Place the given item of type T on top of the stack

		@param item the item of type T to be placed on top of the stack
		*/
		void Push(const T& item);

		/**
		Pop

		Remove the top item from the stack
		*/
		void Pop();

		/**
		Top

		Get a reference to the item at the top of the stack
		
		@return a reference to the item at the top of the stack
		*/
		T& Top();

		/**
		Top (const)

		Get a reference to the item at the top of the stack (const)
		
		@return a reference to the item at the top of the stack
		*/
		const T& Top() const;

		/**
		Size

		Get the current size

		@return the population of items in the stack
		*/
		unsigned int Size() const;

		/**
		Is Empty

		Check if the stack is empty

		@return true if the stack is empty. False if any items are present
		*/
		bool IsEmpty() const;

		/**
		Clear

		Remove all elements from the stack
		*/
		void Clear();

	private:
		/**
		SList used to actually store the data
		*/
		SList<T> mSList;

		/**
		Used to track how many items are in the list
		*/
		unsigned int mSize;
	};

}

#include "Stack.inl"