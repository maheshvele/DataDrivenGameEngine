#pragma once
#include "IXmlParseHelper.h"
#include "ActionExpression.h"
#include "SharedDataWorld.h"

namespace Library
{
	class XMLParseHelperExpression : public IXmlParseHelper
	{
	public:

		/**
		Constructor
		*/
		XMLParseHelperExpression();

		/**
		Destructor
		*/
		~XMLParseHelperExpression();

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
		virtual XMLParseHelperExpression* Clone();		

	private:
		/**
		Convert an infix expression to a postfix one using the shunting yard algorithm

		@param expression a properly formatted infix expression. Operators and operands are seperated via whitespace
		@return a postfix representation of the infix expression parameter
		*/
		SList<std::string> ShuntingYard(const SList<std::string>& expressionTokens);

		/**
		Hashmap of legal operators and their relative precedence values
		*/
		Hashmap<std::string, int> mLegalOperators;

		/**
		String for type comparison
		*/
		static const std::string actionString;
		static const std::string classString;
		static const std::string targetString;
		static const std::string nameString;

	};
}