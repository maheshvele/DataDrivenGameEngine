#include "ParseHelperFoo.h"


namespace Library
{
	ParseHelperFoo::ParseHelperFoo()
	{
	}

	ParseHelperFoo::~ParseHelperFoo()
	{
	}

	void ParseHelperFoo::Initialize()
	{
	}

	bool ParseHelperFoo::StartElementHandler(XmlParseMaster::SharedData* data, std::string name, Hashmap<std::string, std::string>& attributes)
	{
		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		if (data->Is("SharedDataFoo"))
		{
			SharedDataFoo* reinterpereted = reinterpret_cast<SharedDataFoo*>(data);

			//Handle initializing the element itself
			reinterpereted->IncrementDepth();
			reinterpereted->mMap.Insert(std::pair<std::string, std::uint32_t>(name, 0xffffffff)); //Initialize to the max value of an unsigned int, indicating that the value hasn't been assigned yet			
			mElementStack.PushFront(name);//Put the current element into our stack


			//Handle attributes
			if (attributes.ContainsKey("name"))
			{
				reinterpereted->mName = (*(attributes.Find("name"))).second;
			}

			if (attributes.ContainsKey("style"))
			{
				reinterpereted->mStyle = (*(attributes.Find("style"))).second;
			}

			return true;
		}
		return false;
	}

	bool ParseHelperFoo::EndElementHandler(XmlParseMaster::SharedData* data, std::string name)
	{
		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		if (data->Is("SharedDataFoo"))
		{
			SharedDataFoo* reinterpereted = reinterpret_cast<SharedDataFoo*>(data);
			reinterpereted->DecrementDepth();
			mElementStack.PopFront();//Pop the current element from the top of our stack

			return true;
		}

		return false;
	}


	bool ParseHelperFoo::CharDataHandler(XmlParseMaster::SharedData* data, std::string charData, std::uint32_t length)
	{
		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		if (data->Is("SharedDataFoo"))
		{
			SharedDataFoo* reinterpereted = reinterpret_cast<SharedDataFoo*>(data);
			(*(reinterpereted->mMap.Find(mElementStack.Front()))).second = std::stoi(charData);
			return true;
		}

		return false;
	}

	ParseHelperFoo* ParseHelperFoo::Clone()
	{
		ParseHelperFoo* newClone = new ParseHelperFoo();
		
		return newClone;
	}

}
