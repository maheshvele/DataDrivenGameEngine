#pragma once

#include "IXmlParseHelper.h"
#include "ActionIf.h"
#include "SharedDataWorld.h"

namespace Library
{
	class XMLParseHelperIf : public IXmlParseHelper
	{
	public:

		/**
		Constructor
		*/
		XMLParseHelperIf();

		/**
		Destructor
		*/
		~XMLParseHelperIf();

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
		Duplicate this helper. A 'virtual constructor'. Allocates new memory on the heap that must be deleted.

		@return a newly allocated XMLParseHelperUniverse
		*/
		virtual XMLParseHelperIf* Clone();

	private:
		/**
		String for type comparison
		*/
		static const std::string actionString;
		static const std::string classString;
		static const std::string targetString;
		static const std::string nameString;
		static const std::string conditionString;
	};
}