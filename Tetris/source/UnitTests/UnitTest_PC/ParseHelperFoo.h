//A class only used for testing. Sets up things with my SharedDataInt class
#include <stdint.h>
#include "SharedDataFoo.h"
#include "IXmlParseHelper.h"

namespace Library
{
	class ParseHelperFoo : public IXmlParseHelper
	{
	public:
		/**
		Constructor
		*/
		ParseHelperFoo();

		/**
		Virtual destructor
		*/
		~ParseHelperFoo();

		/**
		Initialize the helper. Gets called just before each file is parsed
		*/
		virtual void Initialize();

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
		Duplicate this helper. A 'virtual constructor'
		*/
		virtual ParseHelperFoo* Clone();

	private:
		/**
		Private SList used as a stack. This keeps track of the current element we're on, allowing us to associate integers with elements via our character data handler
		*/
		SList<std::string> mElementStack;

	};
}