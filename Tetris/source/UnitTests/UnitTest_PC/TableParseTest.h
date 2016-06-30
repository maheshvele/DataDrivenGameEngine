#include <cxxtest/TestSuite.h>
#include <crtdbg.h>
#include <fstream>
#include "XMLParseHelperTable.h"

using namespace Library;

class TableTestSuite : public CxxTest::TestSuite
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

	//Ensure that the start and end handlers are working without worrying about character data yet
	void TestParse(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><integer name=\"Ken\" index=\"0\"></integer></table>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		TS_ASSERT_EQUALS(s.Depth(), 0);
		
	}

	//Test out a parse with a slightly more complex format, containing a single integer
	void TestParseInteger(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><integer name=\"Ken\" index=\"0\">10</integer></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type integer with one value of 10 at index zero and the name "Ken"
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 10);
	}

	//Test parse for an array of integers
	void TestParseIntegerArray(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><integer name=\"Ken\" index=\"0\">10</integer><integer name=\"Ken\" index=\"1\">20</integer><integer name=\"Ken\" index=\"2\">30</integer></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type integer named "Ken". This datum has three values
		//Index 0: value = 10
		//Index 1: value = 20
		//Index 2: value = 30
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 3);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(0), 10);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(1), 20);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(2), 30);
	}

	//Test out a parse with a single float
	void TestParseFloat(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><float name=\"Ken\" index=\"0\">10.5</float></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type float with one value of 10 at index zero and the name "Ken"
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::FLOAT);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<float>(), 10.5);
	}

	//Test out a parse with a float array
	void TestParseFloatArray(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><float name=\"Ken\" index=\"0\">10.5</float><float name=\"Ken\" index=\"1\">20.5</float><float name=\"Ken\" index=\"2\">30.0</float></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type float named "Ken". This datum has three values
		//Index 0: value = 10.5
		//Index 1: value = 20.5
		//Index 2: value = 30.0
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::FLOAT);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 3);
		TS_ASSERT_EQUALS(cachedDatum->Get<float>(0), 10.5);
		TS_ASSERT_EQUALS(cachedDatum->Get<float>(1), 20.5);
		TS_ASSERT_EQUALS(cachedDatum->Get<float>(2), 30.0);
	}

	//Test out a parse with a string
	void TestParseString(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><string name=\"Ken\" index=\"0\">Cool</string></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type string with one value of "Cool" at index zero and the name "Ken"
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::STRING);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<std::string>(), "Cool");
	}

	//Test out a parse with a string array
	void TestParseStringArray(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><string name=\"Ken\" index=\"0\">Cool</string><string name=\"Ken\" index=\"1\">Stylish</string><string name=\"Ken\" index=\"2\">Chill</string></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type float named "Ken". This datum has three values
		//Index 0: value = "Cool"
		//Index 1: value = "Stylish"
		//Index 2: value = "Chill"
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::STRING);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 3);
		TS_ASSERT_EQUALS(cachedDatum->Get<std::string>(0), "Cool");
		TS_ASSERT_EQUALS(cachedDatum->Get<std::string>(1), "Stylish");
		TS_ASSERT_EQUALS(cachedDatum->Get<std::string>(2), "Chill");
	}


	//Test out a parse with a vector
	void TestParseVector(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><vector name=\"Ken\" index=\"0\">1.0,1.0,1.0,1.0</vector></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type vector with all values set to 1
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::VECTOR);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<glm::vec4>(), glm::vec4(1.0f));
	}

	//Test out a parse with a vector array
	void TestParseVectorArray(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><vector name=\"Ken\" index=\"0\">1.0,1.0,1.0,1.0</vector><vector name=\"Ken\" index=\"1\">2.0,2.0,2.0,2.0</vector><vector name=\"Ken\" index=\"2\">3.0,3.0,3.0,3.0</vector></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type vector. It should have 3 values
		//Index 0: A vector containing all 1s
		//Index 1: A vector containing all 2s
		//Index 2: A vector containing all 3s
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::VECTOR);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 3);
		TS_ASSERT_EQUALS(cachedDatum->Get<glm::vec4>(0), glm::vec4(1.0f));
		TS_ASSERT_EQUALS(cachedDatum->Get<glm::vec4>(1), glm::vec4(2.0f));
		TS_ASSERT_EQUALS(cachedDatum->Get<glm::vec4>(2), glm::vec4(3.0f));
	}

	//Test out a parse with a matrix
	void TestParseMatrix(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);

		//Note: the format of the matrix character data does not use newlines to represent advancing to the next row. This was changed to adapt to 
		//		the way that expat handles newlines. Instead, semicolons are used as the new delimeter.

		char* string = "<table><matrix name=\"Ken\" index=\"0\">1.0,0.0,0.0,0.0;0.0,1.0,0.0,0.0;0.0,0.0,1.0,0.0;0.0,0.0,0.0,1.0;</matrix></table>";
		int length = strlen(string);
		m.Parse(string, length, false);
		
		//The scope sc should now contain a single datum of type vector with the values across the diagonal set to 1. 
		/*The matrix should look as follows
			1	0	0	0
			0	1	0	0
			0	0	1	0
			0	0	0	1
		*/
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::MATRIX);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<glm::mat4>(), glm::mat4(1.0f));
	}

	//Test out a parse with a matrix array
	void TestParseMatrixArray(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);

		//Note: the format of the matrix character data does not use newlines to represent advancing to the next row. This was changed to adapt to 
		//		the way that expat handles newlines. Instead, semicolons are used as the new delimeter.

		char* string = "<table><matrix name=\"Ken\" index=\"0\">1.0,0.0,0.0,0.0;0.0,1.0,0.0,0.0;0.0,0.0,1.0,0.0;0.0,0.0,0.0,1.0;</matrix><matrix name=\"Ken\" index=\"1\">2.0,0.0,0.0,0.0;0.0,2.0,0.0,0.0;0.0,0.0,2.0,0.0;0.0,0.0,0.0,2.0;</matrix></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type vector with two values 
		/*
		The first matrix should look as follows
		1	0	0	0
		0	1	0	0
		0	0	1	0
		0	0	0	1

		The second matrix should be the same, but with 2s
		2	0	0	0
		0	2	0	0
		0	0	2	0
		0	0	0	2

		*/
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::MATRIX);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 2);
		TS_ASSERT_EQUALS(cachedDatum->Get<glm::mat4>(0), glm::mat4(1.0f));
		TS_ASSERT_EQUALS(cachedDatum->Get<glm::mat4>(1), glm::mat4(2.0f));
	}

	//Test out a parse for multiple datums in the same scope (of the same type)
	void TestParseMultiple(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><integer name=\"Ken\" index=\"0\">10</integer><integer name=\"Octavio\" index=\"0\">20</integer><integer name=\"Maramara\" index=\"0\">30</integer></table>";
		int length = strlen(string);
		m.Parse(string, length, false);


		TS_ASSERT_EQUALS(s.Depth(), 0);

		//The scope sc should now contain 3 datums. 
		//"Ken" with the value 10
		//"Octavio" with the value 20
		//"Maramara" with the value 30
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 10);

		cachedDatum = sc.Find("Octavio");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 20);

		cachedDatum = sc.Find("Maramara");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 30);
	}

	//Test out a parse for multiple datums in the same scope (of the different types)
	void TestParseMultipleTypes(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><integer name=\"Ken\" index=\"0\">10</integer><float name=\"Octavio\" index=\"0\">20.5</float><string name=\"Maramara\" index=\"0\">Cool</string></table>";
		int length = strlen(string);
		m.Parse(string, length, false);


		TS_ASSERT_EQUALS(s.Depth(), 0);

		//The scope sc should now contain 3 datums. 
		//"Ken": an integer with the value 10
		//"Octavio": a float with the value 20.5
		//"Maramara": a string with the value "Cool"
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 10);

		cachedDatum = sc.Find("Octavio");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::FLOAT);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<float>(), 20.5);

		cachedDatum = sc.Find("Maramara");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::STRING);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<std::string>(), "Cool");
	}

	//Test parsing from a file
	void TestParseFromFile(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);

		std::ofstream myFile;
		myFile.open("test.txt");
		myFile << "<table><integer name=\"Ken\" index=\"0\">10</integer><float name=\"Octavio\" index=\"0\">20.5</float><string name=\"Maramara\" index=\"0\">Cool</string></table>";
		myFile.close();
		m.ParseFromFile("test.txt");
		
		TS_ASSERT_EQUALS(m.GetFileName(), "test.txt");
		TS_ASSERT_EQUALS(s.Depth(), 0);

		//The scope sc should now contain 3 datums. 
		//"Ken": an integer with the value 10
		//"Octavio": a float with the value 20.5
		//"Maramara": a string with the value "Cool"		
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 10);

		cachedDatum = sc.Find("Octavio");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::FLOAT);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<float>(), 20.5);

		cachedDatum = sc.Find("Maramara");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::STRING);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<std::string>(), "Cool");
	}

	//Test cloning shared data scope
	void TestCloneData(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><integer name=\"Ken\" index=\"0\">10</integer></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type integer with one value of 10 at index zero and the name "Ken"
		//We will now clone the shared data and ensure that the values match
		XMLParseHelperTable::SharedDataScope* s2 = s.Clone();

		Datum* cachedDatum = sc.Find("Ken");
		Datum* cachedDatum2 = s2->GetScope().Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), cachedDatum2->GetType());
		TS_ASSERT_EQUALS(cachedDatum->Size(), cachedDatum2->Size());
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(), cachedDatum2->Get<int>());

		delete s2;
	}

	//Test cloning parse helper table
	void TestCloneHelper(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;
		
		//Instead of using p as the helper, we will create a clone of it
		XMLParseHelperTable* pClone = p.Clone();
		m.AddHelper(pClone);
		char* string = "<table><integer name=\"Ken\" index=\"0\">10</integer></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type integer with one value of 10 at index zero and the name "Ken"
		Datum* cachedDatum = sc.Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 10);
		
		delete pClone;
	}

	//Test nested scopes
	void TestNested(void)
	{
		Scope sc(10);
		XMLParseHelperTable::SharedDataScope s(&sc);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><table name=\"nest\" index=\"0\"><integer name=\"Ken\" index=\"0\">10</integer></table></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single nested table named "nest" at index 0
		//The nested table should contain an integer named "Ken" at index 0
		Datum* cachedTable = sc.Find("nest");
		TS_ASSERT_EQUALS(cachedTable->GetType(), Datum::TABLE);
		TS_ASSERT_EQUALS(cachedTable->Size(), 1);
		Datum* cachedDatum = cachedTable->Get<Scope*>()->Find("Ken");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 10);
	}

private:
	_CrtMemState startSnapshot;

};