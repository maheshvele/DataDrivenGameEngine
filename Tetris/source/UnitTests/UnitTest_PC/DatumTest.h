#include <cxxtest/TestSuite.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Datum.h"
#include "Foo.h"


using namespace Library;

class DatumTestSuite : public CxxTest::TestSuite
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

	void TestInstantiation(void)
	{
		Datum d;
		TS_ASSERT(d.GetType() == Datum::UNKNOWN);
		TS_ASSERT(d.Size() == 0);
	}

	void TestSetType(void)
	{
		Datum d;
		d.SetType(Datum::INTEGER);
		TS_ASSERT_EQUALS(d.GetType(), Datum::INTEGER);
		TS_ASSERT_THROWS_ANYTHING(d.SetType(Datum::FLOAT));
	}

	void TestInteger(void)
	{
		Datum d(Datum::INTEGER, 2);
		TS_ASSERT_EQUALS(d.GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(d.Size(), 2);

		//Test get and set
		d.Set(10);
		TS_ASSERT_EQUALS(d.Get<int>(), 10);
		d.Set(20, 1);
		TS_ASSERT_EQUALS(d.Get<int>(1), 20);
		TS_ASSERT_THROWS_ANYTHING(d.Get<int>(99));
		TS_ASSERT_THROWS_ANYTHING(d.Get<float>(10));

		//Test copy constructor and, by extension, assignment operator
		Datum d2(d);
		TS_ASSERT_EQUALS(d.Get<int>(), d2.Get<int>());
		TS_ASSERT_EQUALS(d.Get<int>(1), d2.Get<int>(1));
		TS_ASSERT_EQUALS(d.GetType(), d2.GetType());
		TS_ASSERT_EQUALS(d.Size(), d2.Size());

		//Test clear
		d.Clear();
		TS_ASSERT_EQUALS(d.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d.Get<int>());

		//Test set from string
		d2.SetFromString("102");
		TS_ASSERT_EQUALS(d2.Get<int>(), 102);

		//Test to string
		TS_ASSERT_EQUALS(d2.ToString(), "102");

		//Test comparison
		Datum d3(d2);
		TS_ASSERT(d2 == d3);
		TS_ASSERT(d2 != d);

		//Test SetStorage
		int *iArray = new int[2];
		iArray[0] = 10;
		iArray[1] = 20;
		TS_ASSERT_THROWS_ANYTHING(d3.SetStorage(iArray, 2));

		Datum d4;
		d4.SetStorage(iArray, 2);
		TS_ASSERT_EQUALS(d4.Get<int>(), iArray[0]);
		TS_ASSERT_EQUALS(d4.Get<int>(1), iArray[1]);
		TS_ASSERT_EQUALS(d4.Size(), 2);

		delete[] iArray;

		//Test int scalar assignment
		d = 32;
		TS_ASSERT_EQUALS(d.Size(), 1);
		TS_ASSERT_EQUALS(d.Get<int>(), 32);

		//Test scalar comparison
		TS_ASSERT(d == 32);
		TS_ASSERT(d != 256);
	}

	void TestFloat(void)
	{
		Datum d(Datum::FLOAT, 2);
		TS_ASSERT_EQUALS(d.GetType(), Datum::FLOAT);
		TS_ASSERT_EQUALS(d.Size(), 2);

		//Test get and set
		d.Set(10.0f);
		TS_ASSERT_EQUALS(d.Get<float>(), 10.0f);
		d.Set(20.0f, 1);
		TS_ASSERT_EQUALS(d.Get<float>(1), 20.0f);
		TS_ASSERT_THROWS_ANYTHING(d.Get<float>(99));
		TS_ASSERT_THROWS_ANYTHING(d.Get<int>(10));

		//Test copy constructor and, by extension, assignmetn operator
		Datum d2(d);
		TS_ASSERT_EQUALS(d.Get<float>(), d2.Get<float>());
		TS_ASSERT_EQUALS(d.Get<float>(1), d2.Get<float>(1));
		TS_ASSERT_EQUALS(d.GetType(), d2.GetType());
		TS_ASSERT_EQUALS(d.Size(), d2.Size());

		//Test clear
		d.Clear();
		TS_ASSERT_EQUALS(d.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d.Get<float>());

		//Test set from string
		d2.SetFromString("13.130000");
		TS_ASSERT_EQUALS(d2.Get<float>(), 13.13f);

		//Test to string
		TS_ASSERT_EQUALS(d2.ToString(), "13.130000");

		//Test comparison
		Datum d3(d2);
		TS_ASSERT(d2 == d3);
		TS_ASSERT(d2 != d);

		//Test SetStorage
		float *fArray = new float[2];
		fArray[0] = 10.0f;
		fArray[1] = 20.0f;
		TS_ASSERT_THROWS_ANYTHING(d3.SetStorage(fArray, 2));

		Datum d4;
		d4.SetStorage(fArray, 2);
		TS_ASSERT_EQUALS(d4.Get<float>(), fArray[0]);
		TS_ASSERT_EQUALS(d4.Get<float>(1), fArray[1]);
		TS_ASSERT_EQUALS(d4.Size(), 2);

		delete[] fArray;

		//Test scalar assignment
		d = 4.826f;
		TS_ASSERT_EQUALS(d.Size(), 1);
		TS_ASSERT_EQUALS(d.Get<float>(), 4.826f);

		//Test scalar comparison
		TS_ASSERT(d == 4.826f);
		TS_ASSERT(d != 0.1234f);
	}

	void TestVector(void)
	{
		Datum d(Datum::VECTOR, 2);
		TS_ASSERT_EQUALS(d.GetType(), Datum::VECTOR);
		TS_ASSERT_EQUALS(d.Size(), 2);

		//Test get and set
		glm::vec4 v(1.0f);
		glm::vec4 v2(2.0f);
		d.Set(v);
		TS_ASSERT_EQUALS(d.Get<glm::vec4>(), v);
		d.Set(v2, 1);
		TS_ASSERT_EQUALS(d.Get<glm::vec4>(1), v2);
		TS_ASSERT_THROWS_ANYTHING(d.Get<glm::vec4>(99));
		TS_ASSERT_THROWS_ANYTHING(d.Get<int>(10));

		//Test copy constructor and, by extension, assignment operator
		Datum d2(d);
		TS_ASSERT_EQUALS(d.Get<glm::vec4>(), d2.Get<glm::vec4>());
		TS_ASSERT_EQUALS(d.Get<glm::vec4>(1), d2.Get<glm::vec4>(1));
		TS_ASSERT_EQUALS(d.GetType(), d2.GetType());
		TS_ASSERT_EQUALS(d.Size(), d2.Size());

		//Test clear
		d.Clear();
		TS_ASSERT_EQUALS(d.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d.Get<glm::vec4>());

		//Test comparison
		Datum d3(d2);
		TS_ASSERT(d2 == d3);
		TS_ASSERT(d2 != d);

		//Test SetStorage
		glm::vec4 *vArray = new glm::vec4[2];
		vArray[0] = glm::vec4(1.0f);
		vArray[1] = glm::vec4(2.0f);
		TS_ASSERT_THROWS_ANYTHING(d3.SetStorage(vArray, 2));

		Datum d4;
		d4.SetStorage(vArray, 2);
		TS_ASSERT_EQUALS(d4.Get<glm::vec4>(), vArray[0]);
		TS_ASSERT_EQUALS(d4.Get<glm::vec4>(1), vArray[1]);
		TS_ASSERT_EQUALS(d4.Size(), 2);

		delete[] vArray;

		//Test scalar assignment
		d = glm::vec4(1.25f);
		TS_ASSERT_EQUALS(d.Size(), 1);
		TS_ASSERT_EQUALS(d.Get<glm::vec4>(), glm::vec4(1.25f));

		//Test scalar comparison
		TS_ASSERT(d == glm::vec4(1.25f));
		TS_ASSERT(d != glm::vec4(9234.2435f));


		//Test scalar assignment
		d = glm::vec4(1.0f);
		TS_ASSERT_EQUALS(d.Size(), 1);

		//Test scalar comparison
		TS_ASSERT(d == glm::vec4(1.0f));
		TS_ASSERT(d != glm::vec4(2.345f));

		//Test tostring
		TS_ASSERT_EQUALS(d.ToString(), std::string("1.000000,1.000000,1.000000,1.000000"));

		//Test SetFromString
		Datum dFromString(Datum::VECTOR, 1);
		dFromString.SetFromString("1.000000,1.000000,1.000000,1.000000");
		TS_ASSERT_EQUALS(dFromString.Get<glm::vec4>(), glm::vec4(1.0f));
	}

	void TestMatrix(void)
	{
		Datum d(Datum::MATRIX, 2);
		TS_ASSERT_EQUALS(d.GetType(), Datum::MATRIX);
		TS_ASSERT_EQUALS(d.Size(), 2);

		//Test get and set
		glm::mat4 m(1.0f);
		glm::mat4 m2(2.0f);
		d.Set(m);
		TS_ASSERT_EQUALS(d.Get<glm::mat4>(), m);
		d.Set(m2, 1);
		TS_ASSERT_EQUALS(d.Get<glm::mat4>(1), m2);
		TS_ASSERT_THROWS_ANYTHING(d.Get<glm::mat4>(99));
		TS_ASSERT_THROWS_ANYTHING(d.Get<int>(10));

		//Test copy constructor and, by extension, assignment operator
		Datum d2(d);
		TS_ASSERT_EQUALS(d.Get<glm::mat4>(), d2.Get<glm::mat4>());
		TS_ASSERT_EQUALS(d.Get<glm::mat4>(1), d2.Get<glm::mat4>(1));
		TS_ASSERT_EQUALS(d.GetType(), d2.GetType());
		TS_ASSERT_EQUALS(d.Size(), d2.Size());

		//Test clear
		d.Clear();
		TS_ASSERT_EQUALS(d.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d.Get<glm::mat4>());

		//Test comparison
		Datum d3(d2);
		TS_ASSERT(d2 == d3);
		TS_ASSERT(d2 != d);

		//Test SetStorage
		glm::mat4 *mArray = new glm::mat4[2];
		mArray[0] = glm::mat4(1.0f);
		mArray[1] = glm::mat4(2.0f);
		TS_ASSERT_THROWS_ANYTHING(d3.SetStorage(mArray, 2));

		Datum d4;
		d4.SetStorage(mArray, 2);
		TS_ASSERT_EQUALS(d4.Get<glm::mat4>(), mArray[0]);
		TS_ASSERT_EQUALS(d4.Get<glm::mat4>(1), mArray[1]);
		TS_ASSERT_EQUALS(d4.Size(), 2);

		delete[] mArray;

		//Test scalar assignment
		d = glm::mat4(1.25f);
		TS_ASSERT_EQUALS(d.Size(), 1);
		TS_ASSERT_EQUALS(d.Get<glm::mat4>(), glm::mat4(1.25f));

		//Test scalar comparison
		TS_ASSERT(d == glm::mat4(1.25f));
		TS_ASSERT(d != glm::mat4(9234.2435f));

		//Test tostring
		d = glm::mat4(1.0f);
		TS_ASSERT_EQUALS(d.ToString(), std::string("1.000000,0.000000,0.000000,0.000000\n0.000000,1.000000,0.000000,0.000000\n0.000000,0.000000,1.000000,0.000000\n0.000000,0.000000,0.000000,1.000000\n"));
		
		//Test SetFromString
		Datum dFromString(Datum::MATRIX, 1);
		dFromString.SetFromString("1.000000,0.000000,0.000000,0.000000;0.000000,1.000000,0.000000,0.000000;0.000000,0.000000,1.000000,0.000000;0.000000,0.000000,0.000000,1.000000;");
		TS_ASSERT_EQUALS(d2.Get<glm::mat4>(), glm::mat4(1.0f));
	}

	void TestString()
	{
		Datum d(Datum::STRING, 2);
		TS_ASSERT_EQUALS(d.GetType(), Datum::STRING);
		TS_ASSERT_EQUALS(d.Size(), 2);

		//Test get and set
		d.Set("Ken");
		TS_ASSERT_EQUALS(d.Get<std::string>(), "Ken");
		d.Set("Maramara", 1);
		TS_ASSERT_EQUALS(d.Get<std::string>(1), "Maramara");
		TS_ASSERT_THROWS_ANYTHING(d.Get<std::string>(99));
		TS_ASSERT_THROWS_ANYTHING(d.Get<int>(10));

		//Test copy constructor and, by extension, assignmetn operator
		Datum d2(d);
		TS_ASSERT_EQUALS(d.Get<std::string>(), d2.Get<std::string>());
		TS_ASSERT_EQUALS(d.Get<std::string>(1), d2.Get<std::string>(1));
		TS_ASSERT_EQUALS(d.GetType(), d2.GetType());
		TS_ASSERT_EQUALS(d.Size(), d2.Size());

		//Test clear
		d.Clear();
		TS_ASSERT_EQUALS(d.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d.Get<std::string>());

		//Test set from string
		d2.SetFromString("Hello World!");
		TS_ASSERT_EQUALS(d2.Get<std::string>(), "Hello World!");

		//Test to string
		TS_ASSERT_EQUALS(d2.ToString(), "Hello World!");

		//Test comparison
		Datum d3(d2);
		TS_ASSERT(d2 == d3);
		TS_ASSERT(d2 != d);
		
		//Test SetStorage
		std::string *sArray = new std::string[2];
		TS_ASSERT_THROWS_ANYTHING(d3.SetStorage(sArray, 2));

		Datum d4;
		d4.SetStorage(sArray, 2);
		TS_ASSERT_EQUALS(d4.Get<std::string>(), sArray[0]);
		TS_ASSERT_EQUALS(d4.Get<std::string>(1), sArray[1]);
		TS_ASSERT_EQUALS(d4.Size(), 2);

		delete[] sArray;

		//Test scalar assignment
		d = std::string("Emrakul");
		TS_ASSERT_EQUALS(d.Size(), 1);
		TS_ASSERT_EQUALS(d.Get<std::string>(), std::string("Emrakul"));

		//Test scalar comparison
		TS_ASSERT(d == std::string("Emrakul"));
		TS_ASSERT(d != std::string("Kozilek"));

	}

	void TestPointer(void)
	{
		Datum d(Datum::POINTER, 2);
		TS_ASSERT_EQUALS(d.GetType(), Datum::POINTER);
		TS_ASSERT_EQUALS(d.Size(), 2);
		
		//Test get and set
		Foo* r = new Foo(1);
		Foo* r2 = new Foo(10);
		d.Set(r);
		TS_ASSERT_EQUALS(d.Get<RTTI*>(), r);
		d.Set(r2, 1);
		TS_ASSERT_EQUALS(d.Get<RTTI*>(1), r2);
		TS_ASSERT_THROWS_ANYTHING(d.Get<RTTI*>(99));
		TS_ASSERT_THROWS_ANYTHING(d.Get<int>(10));

		//Test copy constructor and, by extension, assignmetn operator
		Datum d2(d);
		TS_ASSERT_EQUALS(d.Get<RTTI*>(), d2.Get<RTTI*>());
		TS_ASSERT_EQUALS(d.Get<RTTI*>(1), d2.Get<RTTI*>(1));
		TS_ASSERT_EQUALS(d.GetType(), d2.GetType());
		TS_ASSERT_EQUALS(d.Size(), d2.Size());

		//Test clear
		d.Clear();
		TS_ASSERT_EQUALS(d.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d.Get<std::string>());

		//Test set from string
		TS_ASSERT_THROWS_ANYTHING(d2.SetFromString("Tarmogoyf"));
		
		//Test to string
		TS_ASSERT_THROWS_ANYTHING(d2.ToString());
				
		//Test comparison
		Datum d3(d2);
		TS_ASSERT(d2 == d3);
		TS_ASSERT(d2 != d);
		
		//Test SetStorage
		RTTI **rArray = new RTTI*[2];
		rArray[0] = r;
		rArray[1] = r2;
		TS_ASSERT_THROWS_ANYTHING(d3.SetStorage(rArray, 2));

		Datum d4;
		d4.SetStorage(rArray, 2);
		TS_ASSERT_EQUALS(d4.Get<RTTI*>(), rArray[0]);
		TS_ASSERT_EQUALS(d4.Get<RTTI*>(1), rArray[1]);
		TS_ASSERT_EQUALS(d4.Size(), 2);
		
		
		//Test scalar assignment
		d = r;
		TS_ASSERT_EQUALS(d.Size(), 1);
		TS_ASSERT_EQUALS(d.Get<RTTI*>(), r);

		
		//Test scalar comparison
		TS_ASSERT(d == r);
		TS_ASSERT(d != r2);

		delete r;
		delete r2;
		delete[] rArray;
	}

	void TestAssignment(void)
	{
		
		//Test alternate assignment paths between external and internal
		Datum d;
		Datum d2(Datum::INTEGER, 2);
		
		int intArray[2];

		intArray[0] = 0;
		intArray[1] = 1;

		d2.Set(10);
		d2.Set(20, 1);

		//Internal = external
		d.SetStorage(intArray, 2);
		TS_ASSERT_THROWS_NOTHING(d2 = d);
		TS_ASSERT_EQUALS(d2.Get<int>(), d.Get<int>());
		TS_ASSERT_EQUALS(d2.Size(), d.Size());
		TS_ASSERT_EQUALS(d2.GetType(), d.GetType());

		//External = internal
		Datum d3;
		d3.SetStorage(intArray, 2);
		TS_ASSERT_THROWS_NOTHING(d = d3);
		TS_ASSERT_EQUALS(d3.Get<int>(), d.Get<int>());
		TS_ASSERT_EQUALS(d3.Size(), d.Size());
		TS_ASSERT_EQUALS(d3.GetType(), d.GetType());
	
		//External = external
		Datum d4;
		d4.SetStorage(intArray, 2);
		TS_ASSERT_THROWS_NOTHING(d4 = d2);
		TS_ASSERT_EQUALS(d4.Get<int>(), d2.Get<int>());
		TS_ASSERT_EQUALS(d4.Size(), d2.Size());
		TS_ASSERT_EQUALS(d4.GetType(), d2.GetType());
	}

private:
	_CrtMemState startSnapshot;
};