#pragma once
#include "IXmlParseHelper.h"
#include "World.h"
#include "SharedDataWorld.h"
#include "ActionList.h"
#include "ActionEvent.h"
#include "ReactionAttributed.h"



namespace Library
{
	class XMLParseHelperUniverse : public IXmlParseHelper
	{
	public:

		/**
		Enum used to keep track of the type of state we're in
		*/
		enum StateType
		{
			PARSING_ENTITY,
			PARSING_SECTOR,
			PARSING_WORLD,
			PARSING_ACTION,
			PARSING_WINDOW
		};

		/**
		Constructor
		*/
		XMLParseHelperUniverse();

		/**
		Destructor
		*/
		~XMLParseHelperUniverse();

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

		@return a newly allocated XMLParseHelperUniverse
		*/
		virtual XMLParseHelperUniverse* Clone();

	private:
		/**
		Private SList used as a stack. This keeps track of the states defined by the current element. This is used by the character data
		handler and the start element handler to figure out the type of the data that is being operated on.
		*/
		SList<StateType> mStateStack;

		/**
		Strings used to verify type comparison
		*/
		static const std::string nameString;
		static const std::string entityString;
		static const std::string sectorString;
		static const std::string worldString;
		static const std::string classString;
		static const std::string actionString;
		static const std::string targetString;
		static const std::string prototypeString;
		static const std::string creationNameString;
		static const std::string subtypeString;
		static const std::string fileNameString;
		static const std::string instanceNameString;
		static const std::string windowString;
		static const std::string windowHeightString;
		static const std::string windowWidthString;
	};

}