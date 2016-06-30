#include "AttributedFoo.h"

namespace Library
{
	AttributedFoo::AttributedFoo()
	{

		/*
		Signature definitions for attributes with initial values
		*/
		//Integer
		testInt = 10;
		InternalAttribute(HP, 1, Datum::INTEGER, &testInt)

		//Integer array
		for (int i = 0; i < 3; i++)
		{
			testIntArray[i] = i;
		}
		InternalAttribute(Items, 3, Datum::INTEGER, testIntArray)

		//Float
		testFloat = 0.98f;
		InternalAttribute(Completion, 1, Datum::FLOAT, &testFloat)

		//Float array
		for (int i = 0; i < 3; i++)
		{
			testFloatArray[i] = 0.5f + i;
		}
		InternalAttribute(Limits, 3, Datum::FLOAT, testFloatArray)

		//Vector
		testVec = glm::vec4(0.1f, 0.2f, 0.3f, 0.4f);
		InternalAttribute(Location, 1, Datum::VECTOR, &testVec)


		//Vector array
		for (int i = 0; i < 3; i++)
		{
			testVecArray[i] = glm::vec4(i + 0.1f, 0.2f, 0.3f, 0.4f);
		}
		InternalAttribute(Towns, 3, Datum::VECTOR, testVecArray)

		//Matrix
		testMat = glm::mat4(1.0f);
		InternalAttribute(TownMap, 1, Datum::MATRIX, &testMat)

		//Matrix array
		for (int i = 0; i < 3; i++)
		{
			testMatArray[i] = glm::mat4(1.0f + i);
		}
		InternalAttribute(WorldMap, 3, Datum::MATRIX, testMatArray)

		//String
		testString = "Ryu";
		InternalAttribute(Rival, 1, Datum::STRING, &testString)

		//String arary
		testStringArray[0] = "Ken";
		testStringArray[1] = "Matt";
		testStringArray[2] = "Calvin";
		InternalAttribute(Kings, 3, Datum::STRING, &testStringArray)

		//Pointer
		testPointer[0] = nullptr;
		InternalAttribute(Pointer, 1, Datum::POINTER, testPointer)

		//Table
		testScope = nullptr;
		InternalAttribute(Table, 1, Datum::TABLE, testScope)

		/*
		Signature definitions for attributes with externally initialized data
		*/

		//Int
		ExternalAttribute(FriendHP, Datum::INTEGER, 1, &testInt)

		//Int array
		ExternalAttribute(FriendItems, Datum::INTEGER, 3, &testIntArray)

		//Float
		ExternalAttribute(FriendCompletion, Datum::FLOAT, 1, &testFloat)

		//Float array
		ExternalAttribute(FriendLimits, Datum::FLOAT, 3, &testFloatArray)

		//Vector
		ExternalAttribute(FriendLocation, Datum::VECTOR, 1, &testVec)

		//Vector array
		ExternalAttribute(FriendTowns, Datum::VECTOR, 3, &testVecArray)

		//Matrix
		ExternalAttribute(FriendTownMap, Datum::MATRIX, 1, &testMat)

		//Matrix array
		ExternalAttribute(FriendWorldMap, Datum::MATRIX, 3, &testMatArray)

		//String
		ExternalAttribute(FriendRival, Datum::STRING, 1, &testString)

		//String array
		ExternalAttribute(FriendKings, Datum::STRING, 3, &testStringArray)

		//Pointer
		ExternalAttribute(FriendPointer, Datum::POINTER, 1, testPointer)

		//Table
		ExternalAttribute(FriendTable, Datum::TABLE, 1, testScope)

		Populate();
	}

	AttributedFoo::~AttributedFoo()
	{
	}
}