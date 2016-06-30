#include "pch.h"
#include "IXmlParseHelper.h"

namespace Library
{

	IXmlParseHelper::IXmlParseHelper()
	{
	}

	void IXmlParseHelper::Initialize()
	{
	}

	bool IXmlParseHelper::StartElementHandler(XmlParseMaster::SharedData* data, std::string name, Hashmap<std::string, std::string>& attributes)
	{
		return false;
	}

	bool IXmlParseHelper::EndElementHandler(XmlParseMaster::SharedData* data, std::string name)
	{
		return false;
	}

	bool IXmlParseHelper::CharDataHandler(XmlParseMaster::SharedData* data, std::string charData, std::uint32_t length)
	{
		return false;
	}

	IXmlParseHelper* IXmlParseHelper::Clone()
	{
		return this;
	}

	IXmlParseHelper::~IXmlParseHelper()
	{
	}

}
