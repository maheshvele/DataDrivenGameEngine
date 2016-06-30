#pragma once
#include "Scope.h"

namespace Library
{
	class Attributed : public Scope
	{
#define DEFAULT_SIZE 10

		RTTI_DECLARATIONS(Attributed, Scope);

	public:
		/**
		Constructor
		*/
		Attributed(std::uint32_t size = DEFAULT_SIZE);

		/**
		Destructor
		*/
		virtual ~Attributed();

		/**
		Copy constructor

		@param rhs the item to be copied
		*/
		Attributed(const Attributed& rhs);

		/**
		Assignment operator

		@param rhs the item to be copied
		@return the item itself with the newly copied values 
		*/
		Attributed& operator=(const Attributed& rhs);

		/**
		Populate the scope with prescribed members
		*/
		void Populate();

		/**
		Given a string, indicate whether the item is a prescribed attribute

		@param name the name of the attribute to search for
		@return true if the attribute is present and prescribed. False otherwise
		*/
		bool IsPrescribedAttribute(const std::string& name) const;

		/**
		Given a string, indicate whether the item is a Auxiliary attribute

		@param name the name of the attribute to search for
		@return true if the attribute is present and auxiliary. False otherwise
		*/
		bool IsAuxiliaryAttribute(const std::string& name) const;

		/**
		Given a string, indicate whether the item is any attribute

		@param name the name of the attribute to search for
		@return true if the attribute is present and prescribed. False otherwise
		*/
		bool IsAttribute(const std::string& name) const;

		/**
		Append a new attribute to our scope. This is represented by a given string and datum

		@param name the name of the new auxiliary attribute
		@return a reference to the newly appended attribute
		*/
		Datum& AppendAuxiliaryAttribute(std::string name);

		/**
		Get the  index of the first auxiliary attribute

		@return an unsigned int representing the inddex
		*/
		std::uint32_t AuxiliaryBegin() const;

	protected:
		/**
		Internal class representing individual signatures
		*/
		class Signature
		{
		public:
			std::string mName;
			Datum::DatumType mType;
			void* mInitialValue;
			std::uint32_t mSize;
			void* mStorage;
		};


		/**
		List of signatures with which to populate the prescribed attributes
		*/
		Hashmap<std::string, Signature> mSignatures;
	public:
		//Macro defined creation of a new prescribed attribute
#define InternalAttribute(Name, Size, Type, InitialValue)						\
	Signature Name;																\
	Name.mName = #Name;															\
	Name.mSize = Size;															\
	Name.mType = Type;															\
	Name.mInitialValue = InitialValue;											\
	mSignatures.Insert(std::pair<std::string, Signature>(Name.mName, Name));

		//Macro defined creation of a new auxiliary attribute
#define ExternalAttribute(Name, Type, Size, Storage)							\
	Signature Name;																\
	Name.mName = #Name;															\
	Name.mType = Type;															\
	Name.mSize = Size;															\
	Name.mStorage = Storage;													\
	mSignatures.Insert(std::pair<std::string, Signature>(Name.mName, Name));


	};


}
