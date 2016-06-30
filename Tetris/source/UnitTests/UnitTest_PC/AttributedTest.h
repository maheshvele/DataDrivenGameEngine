#include <cxxtest/TestSuite.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "AttributedFoo.h"

using namespace Library;

class AttributedTestSuite : public CxxTest::TestSuite
{
public:

	void setUp()
	{
#ifdef _DEBUG
		//Create a snapshot of the current debug heap
		//Used to check for memory leaks
		_CrtMemCheckpoint(&startSnapshot);
#endif
	}

	void tearDown()
	{
#ifdef _DEBUG
		//Compare the memory state at the end to our snapshot at the beginning
		_CrtMemState endSnapshpt, difference;
		_CrtMemCheckpoint(&endSnapshpt);
		if (_CrtMemDifference(&difference, &startSnapshot, &endSnapshpt))
		{
			_CrtMemDumpStatistics(&difference);
		}
#endif
	}

	//Make sure our  signature list is being used to populate correctly
	//Confirm with isattribute
	void TestIsAttribute(void)
	{
		AttributedFoo a;

		TS_ASSERT(a.IsAttribute("this"));
		TS_ASSERT(a.IsAttribute("HP"));
		TS_ASSERT(a.IsAttribute("Items"));
		TS_ASSERT(a.IsAttribute("Completion"));
		TS_ASSERT(a.IsAttribute("Limits"));
		TS_ASSERT(a.IsAttribute("Location"));
		TS_ASSERT(a.IsAttribute("Towns"));
		TS_ASSERT(a.IsAttribute("TownMap"));
		TS_ASSERT(a.IsAttribute("WorldMap"));
		TS_ASSERT(a.IsAttribute("Rival"));
		TS_ASSERT(a.IsAttribute("Kings"));
		TS_ASSERT(a.IsAttribute("Pointer"));
		TS_ASSERT(a.IsAttribute("Table"));
		TS_ASSERT(a.IsAttribute("FriendHP"));
		TS_ASSERT(a.IsAttribute("FriendItems"));
		TS_ASSERT(a.IsAttribute("FriendCompletion"));
		TS_ASSERT(a.IsAttribute("FriendLimits"));
		TS_ASSERT(a.IsAttribute("FriendLocation"));
		TS_ASSERT(a.IsAttribute("FriendTowns"));
		TS_ASSERT(a.IsAttribute("FriendTownMap"));
		TS_ASSERT(a.IsAttribute("FriendWorldMap"));
		TS_ASSERT(a.IsAttribute("FriendRival"));
		TS_ASSERT(a.IsAttribute("FriendKings"));
		TS_ASSERT(a.IsAttribute("FriendPointer"));
		TS_ASSERT(a.IsAttribute("FriendTable"));		

		TS_ASSERT(!(a.IsAttribute("MP")));
	}

	//Ensure that the values of our internal perscribed attributes are as described by the signature list
	void TestInternalValues(void)
	{
		AttributedFoo a;

		Datum *pointHP = a.Find("HP");
		TS_ASSERT_EQUALS((*pointHP).Get<int>(), 10);
		pointHP->Get<int>() = 9;
		TS_ASSERT_EQUALS((*pointHP).Get<int>(), 9);


		Datum *pointItems = a.Find("Items");
		for (int i = 0; i < 3; i++)
		{
			TS_ASSERT_EQUALS((*pointItems).Get<int>(i), i);
		}

		Datum *pointCompletion = a.Find("Completion");
		TS_ASSERT_EQUALS((*pointCompletion).Get<float>(), 0.98f);

		Datum *pointLimits = a.Find("Limits");
		for (int i = 0; i < 3; i++)
		{
			TS_ASSERT_EQUALS((*pointLimits).Get<float>(i), i + 0.5f);
		}

		Datum *pointLocation = a.Find("Location");
		TS_ASSERT_EQUALS((*pointLocation).Get<glm::vec4>(), glm::vec4(0.1f, 0.2f, 0.3f, 0.4f));

		Datum *pointTowns = a.Find("Towns");
		for (int i = 0; i < 3; i++)
		{
			TS_ASSERT_EQUALS((*pointTowns).Get<glm::vec4>(i), glm::vec4(i + 0.1f, 0.2f, 0.3f, 0.4f));
		}

		Datum *pointTownMap = a.Find("TownMap");
		TS_ASSERT_EQUALS((*pointTownMap).Get<glm::mat4>(), glm::mat4(1.0f));

		Datum *pointWorldMap = a.Find("WorldMap");
		for (int i = 0; i < 3; i++)
		{
			TS_ASSERT_EQUALS((*pointWorldMap).Get<glm::mat4>(i), glm::mat4(1.0f + i));
		}

		Datum *pointRival = a.Find("Rival");
		TS_ASSERT_EQUALS((*pointRival).Get<std::string>(), "Ryu");

		Datum *pointKings = a.Find("Kings");
		TS_ASSERT_EQUALS((*pointKings).Get<std::string>(), "Ken");
		TS_ASSERT_EQUALS((*pointKings).Get<std::string>(1), "Matt");
		TS_ASSERT_EQUALS((*pointKings).Get<std::string>(2), "Calvin");

		Datum *pointPointer = a.Find("Pointer");
		TS_ASSERT_EQUALS((*pointPointer).Get<RTTI*>(), nullptr);

		Datum *tablePointer = a.Find("Table");
		TS_ASSERT_DIFFERS((*tablePointer).Get<Scope*>(), nullptr);
	}

	//Ensure external attributes are being populated correctly
	void TestExternalValues(void)
	{
		AttributedFoo a;

		Datum *pointHP = a.Find("FriendHP");
		TS_ASSERT_EQUALS((*pointHP).Get<int>(), 10);


		Datum *pointItems = a.Find("FriendItems");
		for (int i = 0; i < 3; i++)
		{
			TS_ASSERT_EQUALS((*pointItems).Get<int>(i), i);
		}

		Datum *pointCompletion = a.Find("FriendCompletion");
		TS_ASSERT_EQUALS((*pointCompletion).Get<float>(), 0.98f);

		Datum *pointLimits = a.Find("FriendLimits");
		for (int i = 0; i < 3; i++)
		{
			TS_ASSERT_EQUALS((*pointLimits).Get<float>(i), i + 0.5f);
		}

		Datum *pointLocation = a.Find("FriendLocation");
		TS_ASSERT_EQUALS((*pointLocation).Get<glm::vec4>(), glm::vec4(0.1f, 0.2f, 0.3f, 0.4f));

		Datum *pointTowns = a.Find("FriendTowns");
		for (int i = 0; i < 3; i++)
		{
			TS_ASSERT_EQUALS((*pointTowns).Get<glm::vec4>(i), glm::vec4(i + 0.1f, 0.2f, 0.3f, 0.4f));
		}

		Datum *pointTownMap = a.Find("FriendTownMap");
		TS_ASSERT_EQUALS((*pointTownMap).Get<glm::mat4>(), glm::mat4(1.0f));

		Datum *pointWorldMap = a.Find("FriendWorldMap");
		for (int i = 0; i < 3; i++)
		{
			TS_ASSERT_EQUALS((*pointWorldMap).Get<glm::mat4>(i), glm::mat4(1.0f + i));
		}

		Datum *pointRival = a.Find("FriendRival");
		TS_ASSERT_EQUALS((*pointRival).Get<std::string>(), "Ryu");

		Datum *pointKings = a.Find("FriendKings");
		TS_ASSERT_EQUALS((*pointKings).Get<std::string>(), "Ken");
		TS_ASSERT_EQUALS((*pointKings).Get<std::string>(1), "Matt");
		TS_ASSERT_EQUALS((*pointKings).Get<std::string>(2), "Calvin");

		Datum *pointPointer = a.Find("Pointer");
		TS_ASSERT_EQUALS((*pointPointer).Get<RTTI*>(), a.testPointer[0]);
	}

	//Test assignment operator and copy constructor
	void TestCopies(void)
	{
		AttributedFoo a;
		AttributedFoo b;

		b.AppendAuxiliaryAttribute("MP");
		TS_ASSERT(b.Find("MP") != nullptr);
		TS_ASSERT(a.Find("MP") == nullptr);

		a = b;
		TS_ASSERT(a.Find("MP") != nullptr);

	}

	//Test auxiliary begin index
	void TestAuxiliaryBegin(void)
	{
		AttributedFoo a;
	
		//We have 24 prescriped attributes defined in AttributedFoo
		//Including the 'this' pointer, that would set the start index to 25
		TS_ASSERT_EQUALS(a.AuxiliaryBegin(), 25);

	}

	//Differentiate between perscriebd attributes and auxiliary attributes
	void TestPerscribed(void)
	{
		AttributedFoo a;

		TS_ASSERT(a.IsPrescribedAttribute("this"));
		TS_ASSERT(a.IsPrescribedAttribute("HP"));
		TS_ASSERT(a.IsPrescribedAttribute("Items"));
		TS_ASSERT(a.IsPrescribedAttribute("Completion"));
		TS_ASSERT(a.IsPrescribedAttribute("Limits"));
		TS_ASSERT(a.IsPrescribedAttribute("Location"));
		TS_ASSERT(a.IsPrescribedAttribute("Towns"));
		TS_ASSERT(a.IsPrescribedAttribute("TownMap"));
		TS_ASSERT(a.IsPrescribedAttribute("WorldMap"));
		TS_ASSERT(a.IsPrescribedAttribute("Rival"));
		TS_ASSERT(a.IsPrescribedAttribute("Kings"));
		TS_ASSERT(a.IsPrescribedAttribute("Pointer"));
		TS_ASSERT(a.IsPrescribedAttribute("Table"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendHP"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendItems"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendCompletion"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendLimits"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendLocation"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendTowns"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendTownMap"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendWorldMap"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendRival"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendKings"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendPointer"));
		TS_ASSERT(a.IsPrescribedAttribute("FriendTable"));

		TS_ASSERT(!a.IsAuxiliaryAttribute("this"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("HP"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("Items"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("Completion"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("Limits"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("Location"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("Towns"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("TownMap"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("WorldMap"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("Rival"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("Kings"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("Pointer"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("Table"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendHP"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendItems"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendCompletion"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendLimits"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendLocation"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendTowns"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendTownMap"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendWorldMap"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendRival"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendKings"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendPointer"));
		TS_ASSERT(!a.IsAuxiliaryAttribute("FriendTable"));

	}

	//Test adding and checking new auxiliary attributes
	void TestAppendAuxiliary(void)
	{
		AttributedFoo a;
		a.AppendAuxiliaryAttribute("MP");
		TS_ASSERT(a.IsAttribute("MP"));
		TS_ASSERT(!a.IsPrescribedAttribute("MP"));
		TS_ASSERT(a.IsAuxiliaryAttribute("MP"));

	}

private:
	_CrtMemState startSnapshot;
};