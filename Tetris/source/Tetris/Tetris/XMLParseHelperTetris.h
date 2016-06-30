#pragma once
#include "IXmlParseHelper.h"
#include "Board.h"
#include "SharedDataWorld.h"

namespace Library
{
	class XMLParseHelperTetris : public IXmlParseHelper
	{
	public:
		/**
		Constructor
		*/
		XMLParseHelperTetris();

		/**
		Destructor
		*/
		~XMLParseHelperTetris();

		/**
		Set up the helper to parse fresh data
		*/
		void Initialize();

		/**
		Handle the element start with the given name in the given hashmap

		@param name the name of the element to handle
		@param attribuets the hashmap containing the element to handle
		@return true if the element was handled, false otherwise
		*/
		virtual bool StartElementHandler(Library::XmlParseMaster::SharedData* data, std::string name, Library::Hashmap<std::string, std::string>& attributes);

		/**
		Handle the element end with the given name in the given hashmap

		@param name the name of the element to handle
		@return true if the element was handled, false otherwise
		*/
		virtual bool EndElementHandler(Library::XmlParseMaster::SharedData* data, std::string name);

		/**
		Given a string buffer of character data and an integer length, attempt to handle the character data

		@param data the string data to be handled
		@param length the number of characters in data
		@return true if the elemnt was handled, false otherwise
		*/
		virtual bool CharDataHandler(Library::XmlParseMaster::SharedData* data, std::string charData, std::uint32_t length);

		/**
		Duplicate this helper. A 'virtual constructor'. Allocates new memory on the heap that must be deleted.

		@return a newly allocated XMLParseHelperUniverse
		*/
		virtual XMLParseHelperTetris* Clone();
	};
}