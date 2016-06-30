#pragma once

#include <string>
#include "Hashmap.h"
#include "XmlParseMaster.h"

namespace Library
{
	/**
	Abstract base class
	*/
	class IXmlParseHelper
	{
	public:
		/**
		Default constructor
		*/
		IXmlParseHelper();

		/**
		Initialize the helper. Gets called just before each file is parsed
		*/
		virtual void Initialize();

		/**
		Handle the element start with the given name in the given hashmap

		@param data a pointer to the shared data to fill out
		@param name the name of the element to handle
		@param attributes the hashmap containing the attributes
		@return true if the element was handled, false otherwise
		*/
		virtual bool StartElementHandler(XmlParseMaster::SharedData* data, std::string name, Hashmap<std::string, std::string>& attributes);

		/**
		Handle the element end with the given name in the given hashmap

		@param data a pointer to the shared data to fill out
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
		Delete copy constructor. This funcitonality is dealt with by Clone()
		*/
		IXmlParseHelper(const IXmlParseHelper& rhs) = delete;

		/**
		Delete assignment operator
		*/
		IXmlParseHelper& operator=(const IXmlParseHelper& rhs) = delete;

		/**
		Duplicate this helper. A 'virtual constructor'
		*/
		virtual IXmlParseHelper* Clone() = 0;

		/**
		Virtual destructor
		*/
		virtual ~IXmlParseHelper() = 0;
	};
}