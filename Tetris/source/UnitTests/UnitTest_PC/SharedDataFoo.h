#include <stdint.h>
#include "XmlParseMaster.h"
#include "Hashmap.h"
#include "Factory.h"

//Class contains a hashmap of <name, unsigned int> pairs to be filled out by the ParseHelperFoo class
namespace Library
{
	class SharedDataFoo : public XmlParseMaster::SharedData
	{	
		RTTI_DECLARATIONS(SharedDataFoo, SharedData);
	public:
		SharedDataFoo();
		~SharedDataFoo();
		virtual SharedData* Clone();


		/**
		Hashmap containing all of the elements that we find
		*/
		Hashmap<std::string, std::uint32_t> mMap;//Used to store elements and their integer values found in the character data

		/**
		String to be filled with an attribute
		*/
		std::string mName;

		/**
		String to be filled with an attribute
		*/
		std::string mStyle;


	};
}