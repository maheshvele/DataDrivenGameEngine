#pragma once
#include "IXmlParseHelper.h"
#include "Scope.h"
#include "Factory.h"
#include "ActionEvent.h"

namespace Library
{
	class XMLParseHelperTable : public IXmlParseHelper
	{
	public:

		/**
		Internal class used to store handled data in a scope
		*/
		class SharedDataScope : public XmlParseMaster::SharedData
		{
			RTTI_DECLARATIONS(SharedDataScope, SharedData);
		public:
			/**
			Constructor
			*/
			SharedDataScope();

			/**
			Constructor

			@param initialScope the address of the scope to be filled out
			*/
			SharedDataScope(Scope* initialScope);

			/**
			Denstructor
			*/
			~SharedDataScope();

			/**
			Virtual clone function. Allocates new memory on the heap that must be deleted.
		
			@return a newly allocated SharedDataScope which includes a newly allocated copy of the current scope.
			*/
			virtual SharedDataScope* Clone();

			/**
			Get a reference to the scope that is currently being used
			
			@return a reference to the current scope
			*/
			Scope& GetScope();

			/**
			Set the value of the current scope

			@param newAddress the address of the scope to be used
			*/
			void SetScope(Scope* newAddress);

			/**
			Push a new item onto the name stack

			@param name the new name to add to the stack
			*/
			void PushName(const std::string& name);

			/**
			Pop the top off of the name stack
			*/
			void PopName();

			/**
			Check the current top of our name stack 

			@return the name of the current thing we're dealing with
			*/
			std::string PeekName();

			/**
			Push a new item onto the index stack

			@param index the new index to push onto the stack
			*/
			void PushIndex(std::uint32_t index);

			/**
			Pop the top off of the index stack
			*/
			void PopIndex();

			/**
			Check the current top of our index stack

			@return the index of the current thing we're dealing with
			*/
			std::uint32_t PeekIndex();

		private:
			/**
			Scope where data is stored
			*/
			Scope* mScope;

			/**
			The name of the datum we're going to fill out next is at the front of this stack
			*/
			SList<std::string> mNameStack;

			/**
			The index in the current scope that we're in. Used for filling out arrays
			*/
			SList<std::uint32_t> mIndexStack;

			/**
			Flag set to confirm that data has been created from a clone
			*/
			bool mIsClone;
		};
	
		/**
		Enum used to keep track of the type of state we're in
		*/
		enum StateType
		{
			PARSING_INTEGER,
			PARSING_FLOAT,
			PARSING_VECTOR,
			PARSING_MATRIX,
			PARSING_STRING,
			PARSING_TABLE
		};

		/**
		Constructor
		*/
		XMLParseHelperTable();

		/**
		Destructor
		*/
		~XMLParseHelperTable();

		/**
		Sets up the helper to parse fresh data
		*/
		void Initialize();

		/**
		Handle the element start with the given name in the given hashmap

		@param name the name of the element to handle
		@param attribuets the hashmap containing the element to handle
		@return true if the element was handled, false otherwise
		*/
		virtual bool StartElementHandler(XmlParseMaster::SharedData* data, std::string name, Hashmap<std::string, std::string>& attributes);

		/**
		Handle the element end with the given name in the given hashmap

		@param name the name of the element to handle
		@return true if the element was handled, false otherwise
		*/
		virtual bool EndElementHandler(XmlParseMaster::SharedData* data, std::string name);

		/**
		Given a string buffer of character data and an integer length, attempt to handle the character data

		@param data the string data to be handled
		@param length the number of characters in data
		@return true if the elemnt was handled, false otherwise
		*/
		virtual bool CharDataHandler(XmlParseMaster::SharedData* data, std::string charData, std::uint32_t length);

		/**
		Duplicate this helper. A 'virtual constructor'. Allocates new memory on the heap that must be deleted.
		
		@return a newly allocated XMLParseHelperTable
		*/
		virtual XMLParseHelperTable* Clone();

	private:
		/**
		Private SList used as a stack. This keeps track of the name and index where the current data to be handled by the char data handler
		is to be inserted, as defined by the attributes of each XML element. 
		*/
		SList<std::pair<std::string, std::uint32_t>> mInsertionStack;

		/**
		Private SList used as a stack. This keeps track of the states defined by the current element. This is used by the character data
		handler and the start element handler to figure out the type of the data that is being operated on.
		*/
		SList<StateType> mStateStack;

		/**
		Strings used to verify type comparison
		*/
		static const std::string nameString;
		static const std::string indexString;
		static const std::string tableString;
		static const std::string integerString;
		static const std::string floatString;
		static const std::string vectorString;
		static const std::string matrixString;
		static const std::string stringString;
	};

}