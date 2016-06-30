#include <cxxtest/TestSuite.h>
#include <crtdbg.h>
#include <iostream>
#include "Scope.h"
#include "RTTI.H"

using namespace Library;

class ScopeTestSuite : public CxxTest::TestSuite
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

	//Append a scope and then orphan it manually
	void TestOrphan(void)
	{
		Scope s(10);
		Datum &d = s.Append("A");
		d.SetType(Datum::INTEGER);
		d.Set(2);

		Scope* s2 = new Scope(10);
		Datum &d2 = s2->Append("B");
		d2.SetType(Datum::INTEGER);
		d2.Set(5);
		
		std::string temp = "C";
		s.Adopt(s2, temp, 0);
		TS_ASSERT_EQUALS(s2->GetParent(), &s);
		TS_ASSERT_EQUALS(s.Find("C")->Get<Scope*>()->Find("B")->GetType(), d2.GetType());
		TS_ASSERT_EQUALS(s.Find("C")->Get<Scope*>()->Find("B")->Get<int>(), d2.Get<int>());
		TS_ASSERT_EQUALS(s.Find("C")->Get<Scope*>(), s2);

		s2->Orphan();
		TS_ASSERT_EQUALS(s2->GetParent(), nullptr);
		TS_ASSERT_EQUALS(s.Find("C")->Get<Scope*>(), nullptr);
		delete s2;
	}

	void TestAppend(void)
	{
		Scope s(10);
		Datum &d = s.Append("Dragons");
		d.SetType(Datum::INTEGER);
		d.Set(2);
		TS_ASSERT_EQUALS(d.Size(), 1);
		TS_ASSERT_EQUALS(d.GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(s.GetParent(), nullptr);
	}

	void TestFind(void)
	{
		Scope s(10);
		Datum &d = s.Append("Dragons");
		d.SetType(Datum::INTEGER);
		d.Set(2);
		TS_ASSERT_EQUALS(*(s.Find("Dragons")), d);
		TS_ASSERT_EQUALS(nullptr, s.Find("Goblins"));
	}

	void TestBrackets(void)
	{
		Scope s(10);
		Datum &d = s.Append("Elves");
		d.SetType(Datum::INTEGER);
		d.Set(2);
		TS_ASSERT_EQUALS(d, s["Elves"]);
		TS_ASSERT_EQUALS(d, s[0]);
	}
	
	void TestDatumOfScope(void)
	{
		Datum d(Datum::TABLE, 2);
		TS_ASSERT_EQUALS(d.GetType(), Datum::TABLE);
		TS_ASSERT_EQUALS(d.Size(), 2);
	
		Datum d2(Datum::TABLE, 2);
		TS_ASSERT_EQUALS(d2.GetType(), Datum::TABLE);
		TS_ASSERT_EQUALS(d2.Size(), 2);

		Scope s(10);
		s.Append("Dwarves");
		d.Set(&s);
		d2 = &s;
		TS_ASSERT_EQUALS(d2.Get<Scope*>(), d.Get<Scope*>());
	}
	
	void TestAdopt(void)
	{
		Scope s(10);
		Datum &d = s.Append("Zombies");
		d.SetType(Datum::INTEGER);
		d.Set(2);
		
		Scope* s2 = new Scope(10);
		Datum &d2 = s2->Append("Spirits");
		d2.SetType(Datum::INTEGER);
		d2.Set(5);

		std::string temp = "Fire";
		s.Adopt(s2, temp, 0);
		TS_ASSERT_EQUALS(s.Find("Fire")->Get<Scope*>()->Find("Spirits")->GetType(), d2.GetType());
		TS_ASSERT_EQUALS(s.Find("Fire")->Get<Scope*>()->Find("Spirits")->Get<int>(), d2.Get<int>()); 
	}

	void TestAppendScope(void)
	{
		Scope s(10);
		Datum &d = s.Append("Pen");
		d.SetType(Datum::INTEGER);
		d.Set(2);

		Scope s2(10);
		Datum &d2 = s2.Append("Sword");
		d2.SetType(Datum::INTEGER);
		d2.Set(2);
		Scope &sr = s2.AppendScope("Wizard");
		TS_ASSERT_EQUALS(sr.GetParent(), &s2);
	}

	void TestFindName(void)
	{
		Scope s(10);
		Datum &d = s.Append("Pen");
		d.SetType(Datum::INTEGER);
		d.Set(2);

		Scope s2(10);
		Datum &d2 = s2.Append("Sword");
		d2.SetType(Datum::INTEGER);
		d2.Set(2);
		Scope &sr = s2.AppendScope("Wizard");

		TS_ASSERT_EQUALS(sr.GetParent(), &s2);
		TS_ASSERT_EQUALS("Wizard", s2.FindName(&sr));
	}

	void TestSearch(void)
	{
		Scope s(10);
		Datum &d = s.Append("Ky");
		d.SetType(Datum::TABLE);


		Scope* s2 = new Scope(10);
		Datum &d2 = s2->Append("Kiske");

		std::string temp = "Kiske";
		s.Adopt(s2, temp, 0);

		TS_ASSERT_EQUALS(&d2, s2->Search("Kiske"));
		TS_ASSERT_EQUALS(&d, s2->Search("Ky"));
	}

	
	void TestAssignmentAndCopy(void)
	{
		Scope s(10);
		Datum &d = s.Append("Sol");
		d.SetType(Datum::INTEGER);
		d.Set(2);

		Scope s2(10);
		s2 = s;
		
		TS_ASSERT_EQUALS(s.Find("Sol")->Get<int>(), s2.Find("Sol")->Get<int>());
		TS_ASSERT_EQUALS(s.GetParent(), s2.GetParent());

		Datum &d2 = s.Append("Badguy");
		d2.SetType(Datum::TABLE);
		Scope sp(10);
		Datum &dp = sp.Append("Fireseal");
		dp.SetType(Datum::INTEGER);
		dp.Set(999);
		d2.Set(&sp);

		Scope s3(s);

		TS_ASSERT_EQUALS(s3.Find("Sol")->Get<int>(), s2.Find("Sol")->Get<int>());
		TS_ASSERT_EQUALS(s3.GetParent(), s2.GetParent());

		TS_ASSERT_DIFFERS(s3.Find("Badguy"), nullptr);
		TS_ASSERT_DIFFERS(s.Find("Badguy"), nullptr);
		TS_ASSERT_DIFFERS(s3.Find("Badguy"), s.Find("Badguy"));
		
		TS_ASSERT_EQUALS(999, (*((*(s.Find("Badguy"))).Get<Scope*>()->Find("Fireseal"))).Get<int>());
		TS_ASSERT_EQUALS((*((*(s.Find("Badguy"))).Get<Scope*>()->Find("Fireseal"))).Get<int>(), (*((*(s3.Find("Badguy"))).Get<Scope*>()->Find("Fireseal"))).Get<int>());
		
	}
	

	void TestEquality(void)
	{
		Scope s(10);
		Datum &d = s.Append("Venom");
		d.SetType(Datum::INTEGER);
		d.Set(2);

		Scope s2(10);
		s2 = s;

		Scope s3(10);
		Datum &d2 = s3.Append("Zato");
		d2.SetType(Datum::INTEGER);
		d2.Set(1);

		TS_ASSERT(s == s2);
		TS_ASSERT(s != s3);
	}



private:
	_CrtMemState startSnapshot;
};