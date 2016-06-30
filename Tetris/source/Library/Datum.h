#pragma once
#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>
#include "glm/glm.hpp"
#include "RTTI.H"

namespace Library
{
	//Forward declaration
	class Scope;

	/**
	Datum class. Run-time polymorphic array of values
	*/
	class Datum
	{
	public:
		/**
		Enum used to keep track of the type of the data values being held
		*/
		enum DatumType
		{
			UNKNOWN,
			INTEGER,
			FLOAT,
			VECTOR,
			MATRIX,
			STRING,
			POINTER,
			TABLE,
			MAX
		};

		/**
		Union used to hold different types of values
		*/
		union DatumValues
		{
			int* i;
			float* f;
			glm::vec4* v;
			glm::mat4* m;
			std::string* s;
			RTTI** p;
			Scope** sc;

			DatumValues() { i = nullptr; };
		};




		/**
		Default constructor. Initializes datum to be empty. Doesn't allocated any memory
		*/
		Datum();

		/**
		Constructor with a initial type and size
		
		@param type the type of the datum
		@param size the size of the datum
		*/
		Datum(DatumType type, std::uint32_t size);

		/**
		Default destructor.
		*/
		~Datum();

		/**
		Copy constructor

		@param rhs a reference to the datum to copy
		*/
		Datum(const Datum& rhs);

		/**
		Assignment operator

		@param rhs a reference to the datum to copy
		*/
		Datum& operator=(const Datum& rhs);

		/**
		Scalar assignment (int)

		@param rhs a reference to the int to copy
		*/
		Datum& operator=(const int& rhs);

		/**
		Scalar assignment (float)

		@param rhs a reference to the float to copy
		*/
		Datum& operator=(const float& rhs);

		/**
		Scalar assingment (vector)

		@param rhs a reference to the vector to copy
		*/
		Datum& operator=(const glm::vec4& rhs);

		/**
		Scalar assingment (matrix)

		@param rhs a reference to the matrix to copy
		*/
		Datum& operator=(const glm::mat4& rhs);

		/**
		Scalar assignment (string)

		@param rhs a reference to the string to copy
		*/
		Datum& operator=(const std::string& rhs);

		/**
		Scalar assignemnt (pointers)

		@param rhs a reference to the pointer to copy
		*/
		Datum& Datum::operator=(RTTI* rhs);

		/**
		Scalar assignment (scope)

		@param rhs a reference to the pointer to copy
		*/
		Datum& Datum::operator=(Scope* rhs);

		/**
		Bracket operator for syntactically simplified access to nested scopes

		@param index the index of the item to retrieve
		@return the item at the supplied index
		*/
		Scope& Datum::operator[](std::uint32_t index);

		/**
		Equality operator

		@param rhs a reference to the datum to compare with
		@return true if the values are equal. False otherwise
		*/
		bool operator==(const Datum& rhs);

		/**
		Scalar equality operator  (int)

		@param rhs a reference to the int to compare with
		@return true if the values are equal. False otherwise
		*/
		bool operator==(const int& rhs);

		/**
		Scalar equality operator (float)

		@param rhs a reference to the floaat to compare with
		@return true if the values are equal. False otherwise
		*/
		bool operator==(const float& rhs);

		/**
		Scalar equality operator (vector)

		@param rhs a reference to the vector to compare with
		@return true if the values are equal. False otherwise
		*/
		bool operator==(const glm::vec4& rhs);

		/**
		Scalar equality operator (matrix)

		@param rhs a reference to the matrix to compare with
		@return true if the values are equal. False otherwise
		*/
		bool operator==(const glm::mat4& rhs);

		/**
		Scalar equality operator (string)

		@param rhs a reference to the string to compare with
		@return true if the values are equal. False otherwise
		*/
		bool operator==(const std::string& rhs);

		/**
		Scalar equality operator (pointer)

		@param rhs a reference to the pointer to compare with
		@return true if the values are equal. False otherwise
		*/
		bool operator==(const RTTI* rhs);

		/**
		Inequality operator

		@param rhs a reference to the datum to compare with
		@return flase if the values are equal. True otherwise
		*/
		bool operator!=(const Datum& rhs);

		/**
		Scalar inequality operator (int)

		@param rhs a reference to the int to compare with
		@return flase if the values are equal. True otherwise
		*/
		bool operator!=(const int& rhs);

		/**
		Scalar inequality operator (float)

		@param rhs a reference to the float to compare with
		@return flase if the values are equal. True otherwise
		*/
		bool operator!=(const float& rhs);

		/**
		Scalar inequality operator (vector)

		@param rhs a reference to the vector to compare with
		@return flase if the values are equal. True otherwise
		*/
		bool operator!=(const glm::vec4& rhs);

		/**
		Scalar inequality operator (matrxi)

		@param rhs a reference to the matrix to compare with
		@return flase if the values are equal. True otherwise
		*/
		bool operator!=(const glm::mat4& rhs);

		/**
		Scalar inequality operator (string)

		@param rhs a reference to the string to compare with
		@return flase if the values are equal. True otherwise
		*/
		bool operator!=(const std::string& rhs);

		/**
		Scalar inequality operator (pointer)

		@param rhs a reference to the pointer to compare with
		@return flase if the values are equal. True otherwise
		*/
		bool operator!=(RTTI* rhs);

		/**
		Check the current type of data being stored 

		@return the type of the data being stored
		*/
		DatumType GetType() const;

		/**
		Chech the current number of elements

		@return the size of the array
		*/
		std::uint32_t Size() const;

		/**
		Set the type of data stored

		@param newType the new type to set the data to
		*/
		void SetType(DatumType newType);

		/**
		Set the number of values and reserve memory if needed

		@param newSize the size to be set to
		*/
		void SetSize(std::uint32_t newSize);

		/**
		Set the datum to store external data (int version)

		@param newData the external data
		@param newSize the size of the external data
		*/
		void SetStorage(int *newData, std::uint32_t newSize);

		/**
		Set the datum to store external data (float version)

		@param newData the external data
		@param newSize the size of the external data
		*/
		void SetStorage(float *newData, std::uint32_t newSize);

		/**
		Set the datum to store external data (vector version)

		@param newData the external data
		@param newSize the size of the external data
		*/
		void SetStorage(glm::vec4 *newData, std::uint32_t newSize);

		/**
		Set the datum to store external data (matrix version)

		@param newData the external data
		@param newSize the size of the external data
		*/
		void SetStorage(glm::mat4 *newData, std::uint32_t newSize);

		/**
		Set the dadtum to store external data (string version)

		@param newData the external data
		@param newSize the size of the external data
		*/
		void SetStorage(std::string *newData, std::uint32_t newSize);

		/**
		Set the dadtum to store external data (Pointer version)

		@param newData the external data
		@param newSize the size of the external data
		*/
		void SetStorage(RTTI **newData, std::uint32_t newSize);

		/**
		Set the dadtum to store external data (Scope version)

		@param newData the external data
		@param newSize the size of the external data
		*/
		void SetStorage(Scope **newData, std::uint32_t newSize);

		/**
		Set a value at an index in the array (int version)

		@param newInt the new integer to be used
		@param index the index to be set (default zero)
		*/
		void Set(int newInt, std::uint32_t index = 0);

		/**
		Set a value at an index in the array (float version)

		@param newFloat the new value to be used
		@param index the index to be set (default zero)
		*/
		void Set(float newFloat, std::uint32_t index = 0);

		/**
		Set a value at an index in the array (vector version)

		@param newVec the new value to be used
		@param index the index to be set (default zero)
		*/
		void Set(glm::vec4 newVec, std::uint32_t index = 0);

		/**
		Set a value at an index in the array (matrix version)

		@param newMat the new value to be used
		@param index the index to be set (default zero)
		*/
		void Set(glm::mat4 newMat, std::uint32_t index = 0);

		/**
		Set a value at an index in the array (string version)


		@param newString the new value to be used
		@param index the index to be set (default zero)
		*/
		void Set(std::string newString, std::uint32_t index = 0);

		/**
		Set a value at an index in the array (RTTI version)

		@param newPointer the new value to be used
		@param index the index to be set (default zero)
		*/
		void Set(RTTI* newPointer, std::uint32_t index = 0);

		/**
		Set a value at an index in the array (Scope version)

		@param newPointer the new value to be used
		@param index the index to be set (default zero)
		*/
		void Set(Scope* newScope, std::uint32_t index = 0);

		/**
		Get a value at an index in the array (templated)

		@param index the index of the item to retrieve
		*/
		template <typename T>
		T& Get(std::uint32_t index = 0);

		/**
		Clear the array. Does not actually shrink the capacity of the array
		*/
		void Clear();

		/**
		Set the value of an element at a given index (default zero) to the value represented by the given string

		@param stringValue the string to get the data from
		@param index the index of the item to set (default 0)
		*/
		void SetFromString(std::string stringValue, std::uint32_t index = 0);

		/**
		Get a string representation of an element

		@param index the index of the item to set (default 0)
		@return the string representation of the data
		*/
		std::string ToString(std::uint32_t index = 0);

		/**
		Check to see if the datum in question is storing external data

		@return true if data is external. False otherwise
		*/
		bool IsExternal();

		/**
		Get the  size of the datum

		@return the size of the datum
		*/
		std::uint32_t GetSize();

	private:

		/**
		Variable that holds the current type of the datum
		*/
		DatumType mType;

		/**
		Variable that stores the actual values
		*/
		DatumValues mValues;

		/**
		The current number of elements in the datum
		*/
		std::uint32_t mSize;
		
		/**
		The maximum number of elements in the datum
		*/
		std::uint32_t mCapacity;

		/**
		Track internal vs external storage
		*/
		bool mIsExternal;

		/**
		Typedef of memory reserve and copy functions
		*/
		typedef DatumValues(*reserveMemoryFP)(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy);
		
		/**
		Typedef of memory delete functions
		*/
		typedef void(*deleteMemoryFP)(DatumValues& toDelete);

		/**
		Static array of function pointers for reserving memory initialized to a copy of another datumValues
		*/
		static reserveMemoryFP reservePointers[9];

		/**
		Static array of function pointers for deleting memory
		*/
		static deleteMemoryFP deletionPointers[9];

		/**
		Function for allocating memory for ints, filled with copies from an old array

		@param size the size of the array
		@param oldSize the size of the array to copy from
		@param toCopy the DatumValues to copy from
		@return DatumValues the newly allocated copy
		*/
		static DatumValues IntReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy);

		/**
		Function for allocating memory for floats, filled with copies from an old array

		@param size the size of the array
		@param oldSize the size of the array to copy from
		@param toCopy the DatumValues to copy from
		@return DatumValues the newly allocated copy
		*/
		static DatumValues FloatReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy);

		/**
		Funciton for allocating memory for vec4s filled with copies from an old array

		@param size the size of the array
		@param oldSize the size of the array to copy from
		@param toCopy the DatumValues to copy from
		@return DatumValues the newly allocated copy
		*/
		static DatumValues VecReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy);

		/**
		Funciton for allocating memory for mat4s filled with copies from an old array

		@param size the size of the array
		@param oldSize the size of the array to copy from
		@param toCopy the DatumValues to copy from
		@return DatumValues the newly allocated copy
		*/
		static DatumValues MatReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy);

		/**
		Funciton for allocating memory for strings filled with copies from an old array

		@param size the size of the array
		@param oldSize the size of the array to copy from
		@param toCopy the DatumValues to copy from
		@return DatumValues the newly allocated copy
		*/
		static DatumValues StringReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy);

		/**
		Function for allocating memorry for pointers filled with copies from an old array

		@param size the size of the array
		@param oldSize the size of the array to copy from
		@param toCopy the DatumValues to copy from
		@return DatumValues the newly allocated copy
		*/
		static DatumValues PointerReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy);


		/**
		Function for allocating memorry for scopes filled with copies from an old array

		@param size the size of the array
		@param oldSize the size of the array to copy from
		@param toCopy the DatumValues to copy from
		@return DatumValues the newly allocated copy
		*/
		static DatumValues ScopeReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy);

		/**
		Function for deleting memory for ints

		@param toDelete the DatumValues to deletes
		*/
		static void IntDelete(DatumValues& toDelete);
				
		/**
		Function for deleting memory for floats

		@param toDelete the DatumValues to deletes
		*/
		static void FloatDelete(DatumValues& toDelete);

		/**
		Function for deleting memory for vec4s

		@param toDelete the DatumValues to deletes
		*/
		static void VecDelete(DatumValues& toDelete);

		/**
		Function for deleting memory for mat4s

		@param toDelete the DatumValues to deletes
		*/
		static void MatDelete(DatumValues& toDelete);

		/**
		Function for deleting memory for strings

		@param toDelete the DatumValues to deletes
		*/
		static void StringDelete(DatumValues& toDelete);

		/**
		Function for dleeting memory for RTTI pointers

		@param toDelete the DatumValues to deletes
		*/
		static void PointerDelete(DatumValues& toDelete);

		/**
		Function for deleting memory for scopes pointers

		@param toDelete the DatumValues to deletes
		*/
		static void ScopeDelete(DatumValues& toDelete);

	};
}