#include <cxxtest/TestSuite.h>
#include "World.h"

using namespace Library;

class ActionExpressionTestSuite : public CxxTest::TestSuite
{
public:

	void setUp()
	{
#ifdef _DEBUG
		//Create a snapshot of the current debug heap
		//Used to check for memory leaks
		_CrtMemCheckpoint(&startSnapshot);
#endif
		mAE = new ActionExpression("Evaluator");
	}

	void tearDown()
	{
		delete mAE;
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


	//Make sure we can initalize an action expression
	void TestInitialization(void)
	{
		TS_ASSERT_DIFFERS(nullptr, mAE);
		TS_ASSERT_EQUALS(mAE->Name(), "Evaluator");
	}

	//Test getters and setters for expression
	void TestGetAndSet(void)
	{
		Datum* target = new Datum(Datum::INTEGER, 1);
		SList<std::string> tokens;
		tokens.PushBack("2");
		tokens.PushBack("2");
		tokens.PushBack("+");
		
		mAE->SetExpression(tokens);
		TS_ASSERT_EQUALS(mAE->GetExpression().Front(), tokens.Front());
		TS_ASSERT_EQUALS(mAE->GetExpression().Back(), tokens.Back());
		mAE->SetTarget(target);
		TS_ASSERT_EQUALS(target, mAE->GetTarget());
	
		delete target;
	}

	//Test evaluating integer addition
	void TestIntAddition(void)
	{
		Datum* target = new Datum(Datum::INTEGER, 1);
		WorldState ws;
		SList<std::string> tokens;
		tokens.PushBack("2");
		tokens.PushBack("2");
		tokens.PushBack("+");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));		
		TS_ASSERT_EQUALS(target->Get<int>(), 4);

		delete target;
	}

	//Test evaluating integer subtraction
	void TestIntSubtraction(void)
	{
		Datum* target = new Datum(Datum::INTEGER, 1);
		WorldState ws;
		SList<std::string> tokens;
		tokens.PushBack("4");
		tokens.PushBack("2");
		tokens.PushBack("-");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 2);

		delete target;
	}

	//Test evaluating integer multiplication
	void TestIntMultiplication(void)
	{
		Datum* target = new Datum(Datum::INTEGER, 1);
		WorldState ws;
		SList<std::string> tokens;
		tokens.PushBack("3");
		tokens.PushBack("5");
		tokens.PushBack("*");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 15);

		delete target;
	}

	//Test evaluating integer division
	void TestIntDivision(void)
	{
		Datum* target = new Datum(Datum::INTEGER, 1);
		WorldState ws;
		SList<std::string> tokens;
		tokens.PushBack("15");
		tokens.PushBack("5");
		tokens.PushBack("/");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 3);

		delete target;
	}

	//Test evaluating integer mod
	void TestIntMod(void)
	{
		Datum* target = new Datum(Datum::INTEGER, 1);
		WorldState ws;
		SList<std::string> tokens;
		tokens.PushBack("15");
		tokens.PushBack("10");
		tokens.PushBack("%");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 5);

		delete target;
	}

	//Test evaluating a more complex expression with many operations using integers
	void TestIntComplex(void)
	{
		Datum* target = new Datum(Datum::INTEGER, 1);
		WorldState ws;
		SList<std::string> tokens;
		tokens.PushBack("3");
		tokens.PushBack("3");
		tokens.PushBack("5");
		tokens.PushBack("*");
		tokens.PushBack("+");
		tokens.PushBack("3");
		tokens.PushBack("/");
		tokens.PushBack("1");
		tokens.PushBack("-");


		mAE->SetExpression(tokens);
		//This  expands to ((3 * 5 + 3) / 3) - 1 = 5

		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 5);

		delete target;
	}

	//Test float addition
	void TestFloatAddition(void)
	{
		Datum* target = new Datum(Datum::FLOAT, 1);
		WorldState ws;
		SList<std::string> tokens;
		tokens.PushBack("2.0");
		tokens.PushBack("2.5");
		tokens.PushBack("+");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<float>(), 4.5);

		delete target;
	}

	//Test float subtraction
	void TestFloatSubtraction(void)
	{
		Datum* target = new Datum(Datum::FLOAT, 1);
		WorldState ws;

		SList<std::string> tokens;
		tokens.PushBack("4.5");
		tokens.PushBack("3.0");
		tokens.PushBack("-");

		mAE->SetExpression(tokens);

		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<float>(), 1.5);

		delete target;
	}

	//Test float multiplication
	void TestFloatMultiplication(void)
	{
		Datum* target = new Datum(Datum::FLOAT, 1);
		WorldState ws;

		SList<std::string> tokens;
		tokens.PushBack("4.5");
		tokens.PushBack("3.0");
		tokens.PushBack("*");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<float>(), 13.5);

		delete target;
	}

	//Test float division
	void TestFloatDivision(void)
	{
		Datum* target = new Datum(Datum::FLOAT, 1);
		WorldState ws;

		SList<std::string> tokens;
		tokens.PushBack("5.0");
		tokens.PushBack("2.0");
		tokens.PushBack("/");

		mAE->SetExpression(tokens);

		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<float>(), 2.5);

		delete target;
	}

	//Test float mod
	void TestFloatMod(void)
	{
		Datum* target = new Datum(Datum::FLOAT, 1);
		WorldState ws;
		SList<std::string> tokens;
		tokens.PushBack("15.75");
		tokens.PushBack("10.0");
		tokens.PushBack("%");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<float>(), 5.75);

		delete target;
	}

	//Test a complex expression with many operations using floats
	void TestFloatComplex(void)
	{
		Datum* target = new Datum(Datum::FLOAT, 1);
		WorldState ws;

		SList<std::string> tokens;
		tokens.PushBack("3.75");
		tokens.PushBack("3.5");
		tokens.PushBack("5.5");
		tokens.PushBack("*");
		tokens.PushBack("+");
		tokens.PushBack("2.0");
		tokens.PushBack("/");
		tokens.PushBack("1.75");
		tokens.PushBack("-");

		mAE->SetExpression(tokens);
		//This  expands to ((3.75 * 5.5 + 3.5) / 2.0) - 1.75 = 9.75

		mAE->SetTarget(target);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<float>(), 9.75);

		delete target;
	}

	//Test equality operator
	void TestEqual(void)
	{
		WorldState ws;
		Datum* target = new Datum(Datum::INTEGER, 1);
		Datum* fTarget = new Datum(Datum::FLOAT, 1);
		SList<std::string> tokens;
		tokens.PushBack("1");
		tokens.PushBack("1");
		tokens.PushBack("==");
		SList<std::string> fTokens;
		fTokens.PushBack("2.5");
		fTokens.PushBack("3.72");
		fTokens.PushBack("==");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_EQUALS(target, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 1);

		mAE->SetExpression(fTokens);
		mAE->SetTarget(fTarget);
		TS_ASSERT_EQUALS(fTarget, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(fTarget->Get<float>(), 0);

		delete target;
		delete fTarget;
	}

	//Test not equal operator
	void TestNotEqual(void)
	{
		WorldState ws;
		Datum* target = new Datum(Datum::INTEGER, 1);
		Datum* fTarget = new Datum(Datum::FLOAT, 1);
		SList<std::string> tokens;
		tokens.PushBack("1");
		tokens.PushBack("1");
		tokens.PushBack("!=");
		SList<std::string> fTokens;
		fTokens.PushBack("2.5");
		fTokens.PushBack("3.72");
		fTokens.PushBack("!=");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_EQUALS(target, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 0);

		mAE->SetExpression(fTokens);
		mAE->SetTarget(fTarget);
		TS_ASSERT_EQUALS(fTarget, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(fTarget->Get<float>(), 1);

		delete target;
		delete fTarget;
	}

	//Test >= operator
	void TestGreaterThanOrEqual(void)
	{
		WorldState ws;
		Datum* target = new Datum(Datum::INTEGER, 1);
		Datum* fTarget = new Datum(Datum::FLOAT, 1);
		SList<std::string> tokens;
		tokens.PushBack("1");
		tokens.PushBack("2");
		tokens.PushBack(">=");
		SList<std::string> fTokens;
		fTokens.PushBack("2.5");
		fTokens.PushBack("2.5");
		fTokens.PushBack(">=");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_EQUALS(target, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 0);

		mAE->SetExpression(fTokens);
		mAE->SetTarget(fTarget);
		TS_ASSERT_EQUALS(fTarget, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(fTarget->Get<float>(), 1);

		delete target;
		delete fTarget;
	}

	//Test <= operator
	void TestLessThanOrEqual(void)
	{
		WorldState ws;
		Datum* target = new Datum(Datum::INTEGER, 1);
		Datum* fTarget = new Datum(Datum::FLOAT, 1);
		SList<std::string> tokens;
		tokens.PushBack("2");
		tokens.PushBack("1");
		tokens.PushBack("<=");
		SList<std::string> fTokens;
		fTokens.PushBack("2.5");
		fTokens.PushBack("2.5");
		fTokens.PushBack(">=");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_EQUALS(target, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 0);

		mAE->SetExpression(fTokens);
		mAE->SetTarget(fTarget);
		TS_ASSERT_EQUALS(fTarget, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(fTarget->Get<float>(), 1);

		delete target;
		delete fTarget;
	}

	//Test > operator
	void TestGreaterThan(void)
	{
		WorldState ws;
		Datum* target = new Datum(Datum::INTEGER, 1);
		Datum* fTarget = new Datum(Datum::FLOAT, 1);
		SList<std::string> tokens;
		tokens.PushBack("1");
		tokens.PushBack("2");
		tokens.PushBack(">");
		SList<std::string> fTokens;
		fTokens.PushBack("5.5");
		fTokens.PushBack("2.5");
		fTokens.PushBack(">");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_EQUALS(target, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 0);

		mAE->SetExpression(fTokens);
		mAE->SetTarget(fTarget);
		TS_ASSERT_EQUALS(fTarget, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(fTarget->Get<float>(), 1);

		delete target;
		delete fTarget;
	}

	//Test < operator
	void TestLessThan(void)
	{
		WorldState ws;
		Datum* target = new Datum(Datum::INTEGER, 1);
		Datum* fTarget = new Datum(Datum::FLOAT, 1);
		SList<std::string> tokens;
		tokens.PushBack("1");
		tokens.PushBack("2");
		tokens.PushBack("<");
		SList<std::string> fTokens;
		fTokens.PushBack("5.5");
		fTokens.PushBack("2.5");
		fTokens.PushBack("<");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_EQUALS(target, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 1);

		mAE->SetExpression(fTokens);
		mAE->SetTarget(fTarget);
		TS_ASSERT_EQUALS(fTarget, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(fTarget->Get<float>(), 0);

		delete target;
		delete fTarget;
	}

	//Test ! operator
	void TestNot(void)
	{
		WorldState ws;
		Datum* target = new Datum(Datum::INTEGER, 1);
		Datum* fTarget = new Datum(Datum::FLOAT, 1);
		SList<std::string> tokens;
		tokens.PushBack("0");
		tokens.PushBack("!");
		SList<std::string> fTokens;
		fTokens.PushBack("2.5");
		fTokens.PushBack("!");

		mAE->SetExpression(tokens);
		mAE->SetTarget(target);
		TS_ASSERT_EQUALS(target, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(target->Get<int>(), 1);

		mAE->SetExpression(fTokens);
		mAE->SetTarget(fTarget);
		TS_ASSERT_EQUALS(fTarget, mAE->GetTarget());
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(fTarget->Get<float>(), 0);

		delete target;
		delete fTarget;
	}

	//Test factory creation in entity
	void TestCreateInEntity(void)
	{
		World w;
		WorldState ws;
		Entity e("Ken");

		e.CreateAction("ActionExpression", "Friction");
		Scope* friction = e.Actions()->Find("Friction")->Get<Scope*>();
		TS_ASSERT_DIFFERS(friction, nullptr);
		TS_ASSERT(friction->Is("ActionExpression"));
		TS_ASSERT_EQUALS(friction->As<Action>()->Name(), "Friction");

	}

	//Test factory creation in actionlist
	void TestCreateInActionList(void)
	{
		World w;
		WorldState ws;
		ActionList al;

		al.CreateAction("ActionExpression", "Friction");
		Scope* friction = al.Actions()->Find("Friction")->Get<Scope*>();
		TS_ASSERT_DIFFERS(friction, nullptr);
		TS_ASSERT(friction->Is("ActionExpression"));
		TS_ASSERT_EQUALS(friction->As<Action>()->Name(), "Friction");
	}


	//Test editing variables
	void TestVariables(void)
	{
		WorldState ws;
		SList<std::string> tokens;
		tokens.PushBack("this.Arg");
		tokens.PushBack("2");
		tokens.PushBack("+");
		
		Entity e("Ken");
		Sector s("Florida");

		Datum& arg = e.Append("Arg");
		arg.SetType(Datum::INTEGER);
		arg.Set(2);

		e.SetSector(&s);

		mAE->SetEntity(&e);

		mAE->SetExpression(tokens);
		mAE->SetTarget(&arg);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(arg.Get<int>(), 4);
		TS_ASSERT_THROWS_NOTHING(mAE->Update(ws));
		TS_ASSERT_EQUALS(arg.Get<int>(), 6);

		e.Orphan();
		mAE->Orphan();
	}


private:
	ActionExpression* mAE;
	_CrtMemState startSnapshot;
};