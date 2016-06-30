#include "pch.h"
#include <iostream>
#include <fstream>
#include "XmlParseMaster.h"
#include "IXmlParseHelper.h"
#include <algorithm>

namespace Library
{
	
	//Shared Data functions
#pragma region SharedData

	//Set up shared data to have definitions
	RTTI_DEFINITIONS(XmlParseMaster::SharedData);

	XmlParseMaster::SharedData::SharedData() :
		mDepth(0), mMaster(nullptr)
	{
	}

	void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster *address)
	{
		mMaster = address;
	}

	XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster()
	{
		return mMaster;
	}

	void  XmlParseMaster::SharedData::IncrementDepth()
	{
		mDepth++;
	}

	void XmlParseMaster::SharedData::DecrementDepth()
	{
		if (mDepth > 0)
		{
			mDepth--;
		}
		else
		{
			throw std::exception("Cannot decrement depth of zero");
		}
	}

	std::uint32_t XmlParseMaster::SharedData::Depth()
	{
		return mDepth;
	}

	XmlParseMaster::SharedData* XmlParseMaster::SharedData::Clone()
	{
		return new SharedData();
	}

#pragma endregion

	/*Parse master functions*/

	//Constructor
	XmlParseMaster::XmlParseMaster(XmlParseMaster::SharedData* newData) :
		mIsClone(false)
	{
		mSharedData = newData;
		if (newData)
		{
			mSharedData->SetXmlParseMaster(this);
		}

		mParser = XML_ParserCreate(NULL);
		if (!mParser) 
		{
			throw std::exception("Couldn't allocate memory for parser\n");
		}

		XML_SetElementHandler(mParser, &XmlParseMaster::StartElementHandler, &XmlParseMaster::EndElementHandler);
		XML_SetUserData(mParser, mSharedData);
		XML_SetCharacterDataHandler(mParser, &XmlParseMaster::CharDataHandler);
	}

	XmlParseMaster::~XmlParseMaster()
	{
		//If we're a clone, delete our sharedData and our helpers
		if (mIsClone)
		{
			delete mSharedData;
			
			while (!mHelpers.IsEmpty())
			{
				delete mHelpers.Back();
				mHelpers.PopBack();
			}
		}

		XML_ParserFree(mParser);
	}

	//Handle start elements
	void XmlParseMaster::StartElementHandler(void *data, const char *element, const char **attribute)
	{
		if (!data || !element || !attribute)
		{
			throw std::exception("Null pointer exception");
		}

		//Reinterperet the data as a shared data
		SharedData *reinterpreted = reinterpret_cast<SharedData*>(data);
		if (reinterpreted == nullptr)
		{
			return;
		}


		XmlParseMaster* curMaster = reinterpreted->GetXmlParseMaster();
		Hashmap <std::string, std::string> organizedAttributes(10);

		//Organized the attributes into a hashmap
		for (int i = 0; attribute[i]; i += 2) 
		{
			std::pair<std::string, std::string> newItem;// = new std::pair<std::string, std::string>;
			newItem.first = attribute[i];
			newItem.second = attribute[i + 1];
			organizedAttributes.Insert(newItem);
		}

		//Go through the chain of responsibility, breaking when we find a handler that works
		for (std::uint32_t i = 0; i < curMaster->mHelpers.Size(); i++)
		{
			if (curMaster->mHelpers.At(i)->StartElementHandler(reinterpreted, std::string(element), organizedAttributes))
			{
				break;
			}
		}
	}

	//Handle end elements
	void XmlParseMaster::EndElementHandler(void *data, const char *element)
	{
		if (!data || !element)
		{
			throw std::exception("Null pointer exception");
		}

		//Reinterperet the data as a shared data
		SharedData *reinterpreted = reinterpret_cast<SharedData*>(data);
		if (reinterpreted == nullptr)
		{
			return;
		}

		XmlParseMaster* curMaster = reinterpreted->GetXmlParseMaster();
		
		//Go through the chain of responsibility, breaking when we find a handler that works
		for (std::uint32_t i = 0; i < curMaster->mHelpers.Size(); i++)
		{
			if (curMaster->mHelpers.At(i)->EndElementHandler(reinterpreted, std::string(element)))
			{
				break;
			}
		}
	}

	//Handle character data
	void XmlParseMaster::CharDataHandler(void *data, const char *content, int length)
	{
		if (!data || !content)
		{
			throw std::exception("Null pointer exception");
		}

		//Reinterperet the data as a shared data
		SharedData *reinterpreted = reinterpret_cast<SharedData*>(data);
		if (reinterpreted == nullptr)
		{
			return;
		}

		XmlParseMaster* curMaster = reinterpreted->GetXmlParseMaster();

		//Go through the chain of responsibility, breaking when we find a handler that works
		for (std::uint32_t i = 0; i < curMaster->mHelpers.Size(); i++)
		{
			if (curMaster->mHelpers.At(i)->CharDataHandler(reinterpreted, content, length))
			{
				break;
			}
		}

	}

	//Parse a given string
	void XmlParseMaster::Parse(const char* buffer, std::uint32_t length, bool isEnd)
	{
		if (!buffer)
		{
			throw std::exception("Buffer to parse is null");
		}

		for (std::uint32_t i = 0; i < mHelpers.Size(); i++)
		{
			mHelpers.At(i)->Initialize();
		}

		if (!XML_Parse(mParser, buffer, length, isEnd))
		{
			throw std::exception("Parse error");
		}
	}

	//Add a helper to our list of helpers
	void XmlParseMaster::AddHelper(IXmlParseHelper* newHelper)
	{
		if (!newHelper)
		{
			throw std::exception("Helper is null");
		}

		mHelpers.PushBack(newHelper);
	}

	//Remove a helper from our list of helpers
	void XmlParseMaster::RemoveHelper(IXmlParseHelper* toRemove)
	{
		if (!toRemove)
		{
			throw std::exception("Helper is null");
		}

		mHelpers.Remove(mHelpers.Find(toRemove));
	}

	//Get the address of our current shared data
	XmlParseMaster::SharedData* XmlParseMaster::GetSharedData()
	{
		return mSharedData;
	}

	//Set the address of our current shared data
	void XmlParseMaster::SetSharedData(XmlParseMaster::SharedData* newSharedData)
	{
		mSharedData = newSharedData;
		if (newSharedData)
		{
			mSharedData->SetXmlParseMaster(this);
		}
	}

	//Parse from a file
	void XmlParseMaster::ParseFromFile(std::string filename)
	{

		std::ifstream is(filename, std::ifstream::binary);
		if (is) 
		{
			mFileName = filename;

			// get length of file:
			is.seekg(0, is.end);
			int length = (int)is.tellg();
			is.seekg(0, is.beg);

			// allocate memory:
			char * buffer = new char[length];
			// read data as a block:
			is.read(buffer, length);
			is.close();

			std::string s(buffer);
			s = s.substr(0, length);
			std::string result;

			std::remove_copy(s.begin(), s.end(), std::back_inserter(result), '\r');
			s = result;
			result.clear();

			std::remove_copy(s.begin(), s.end(), std::back_inserter(result), '\n');
			s = result;
			result.clear();

			std::remove_copy(s.begin(), s.end(), std::back_inserter(result), '\t');
			s = result;
			result.clear();

			// parse content:
			Parse(s.c_str(), s.length(), true);

			delete[] buffer;
		}
	}

	//Get the file name
	std::string XmlParseMaster::GetFileName()
	{

		return mFileName;
	}

	//Create a new copy of this parse master
	XmlParseMaster* XmlParseMaster::Clone()
	{
		SharedData* clonedData;
		XmlParseMaster* clonedMaster;

		if (mSharedData != nullptr)
		{
			clonedData = mSharedData->Clone();
			clonedMaster = new XmlParseMaster(clonedData);
		}
		else
		{
			clonedMaster = new XmlParseMaster(nullptr);
		}

		for (std::uint32_t i = 0; i < mHelpers.Size(); i++)
		{
			clonedMaster->AddHelper(mHelpers[i]->Clone());
		}

		clonedMaster->mIsClone = true;

		return clonedMaster;
	}

}