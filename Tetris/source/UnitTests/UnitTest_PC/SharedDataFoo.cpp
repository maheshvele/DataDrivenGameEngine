#include "SharedDataFoo.h"

namespace Library
{
	RTTI_DEFINITIONS(SharedDataFoo); 

	SharedDataFoo::SharedDataFoo() :
		mMap(10)
	{
	}

	SharedDataFoo::~SharedDataFoo()
	{
		mMap.Clear();
	}

	XmlParseMaster::SharedData* SharedDataFoo::Clone()
	{
		SharedDataFoo* clonedData = new SharedDataFoo();
		clonedData->mName = mName;
		clonedData->mStyle = mStyle;
		clonedData->mMap = mMap;

		return clonedData;
	}

}