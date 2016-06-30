/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_TableTestSuite_init = false;
#include "TableParseTest.h"

static TableTestSuite suite_TableTestSuite;

static CxxTest::List Tests_TableTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TableTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/TableParseTest.h", 8, "TableTestSuite", suite_TableTestSuite, Tests_TableTestSuite );

static class TestDescription_suite_TableTestSuite_TestParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParse() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 35, "TestParse" ) {}
 void runTest() { suite_TableTestSuite.TestParse(); }
} testDescription_suite_TableTestSuite_TestParse;

static class TestDescription_suite_TableTestSuite_TestParseInteger : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseInteger() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 52, "TestParseInteger" ) {}
 void runTest() { suite_TableTestSuite.TestParseInteger(); }
} testDescription_suite_TableTestSuite_TestParseInteger;

static class TestDescription_suite_TableTestSuite_TestParseIntegerArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseIntegerArray() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 72, "TestParseIntegerArray" ) {}
 void runTest() { suite_TableTestSuite.TestParseIntegerArray(); }
} testDescription_suite_TableTestSuite_TestParseIntegerArray;

static class TestDescription_suite_TableTestSuite_TestParseFloat : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseFloat() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 97, "TestParseFloat" ) {}
 void runTest() { suite_TableTestSuite.TestParseFloat(); }
} testDescription_suite_TableTestSuite_TestParseFloat;

static class TestDescription_suite_TableTestSuite_TestParseFloatArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseFloatArray() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 117, "TestParseFloatArray" ) {}
 void runTest() { suite_TableTestSuite.TestParseFloatArray(); }
} testDescription_suite_TableTestSuite_TestParseFloatArray;

static class TestDescription_suite_TableTestSuite_TestParseString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseString() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 142, "TestParseString" ) {}
 void runTest() { suite_TableTestSuite.TestParseString(); }
} testDescription_suite_TableTestSuite_TestParseString;

static class TestDescription_suite_TableTestSuite_TestParseStringArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseStringArray() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 162, "TestParseStringArray" ) {}
 void runTest() { suite_TableTestSuite.TestParseStringArray(); }
} testDescription_suite_TableTestSuite_TestParseStringArray;

static class TestDescription_suite_TableTestSuite_TestParseVector : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseVector() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 188, "TestParseVector" ) {}
 void runTest() { suite_TableTestSuite.TestParseVector(); }
} testDescription_suite_TableTestSuite_TestParseVector;

static class TestDescription_suite_TableTestSuite_TestParseVectorArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseVectorArray() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 208, "TestParseVectorArray" ) {}
 void runTest() { suite_TableTestSuite.TestParseVectorArray(); }
} testDescription_suite_TableTestSuite_TestParseVectorArray;

static class TestDescription_suite_TableTestSuite_TestParseMatrix : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseMatrix() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 233, "TestParseMatrix" ) {}
 void runTest() { suite_TableTestSuite.TestParseMatrix(); }
} testDescription_suite_TableTestSuite_TestParseMatrix;

static class TestDescription_suite_TableTestSuite_TestParseMatrixArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseMatrixArray() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 263, "TestParseMatrixArray" ) {}
 void runTest() { suite_TableTestSuite.TestParseMatrixArray(); }
} testDescription_suite_TableTestSuite_TestParseMatrixArray;

static class TestDescription_suite_TableTestSuite_TestParseMultiple : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseMultiple() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 302, "TestParseMultiple" ) {}
 void runTest() { suite_TableTestSuite.TestParseMultiple(); }
} testDescription_suite_TableTestSuite_TestParseMultiple;

static class TestDescription_suite_TableTestSuite_TestParseMultipleTypes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseMultipleTypes() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 338, "TestParseMultipleTypes" ) {}
 void runTest() { suite_TableTestSuite.TestParseMultipleTypes(); }
} testDescription_suite_TableTestSuite_TestParseMultipleTypes;

static class TestDescription_suite_TableTestSuite_TestParseFromFile : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestParseFromFile() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 374, "TestParseFromFile" ) {}
 void runTest() { suite_TableTestSuite.TestParseFromFile(); }
} testDescription_suite_TableTestSuite_TestParseFromFile;

static class TestDescription_suite_TableTestSuite_TestCloneData : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestCloneData() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 413, "TestCloneData" ) {}
 void runTest() { suite_TableTestSuite.TestCloneData(); }
} testDescription_suite_TableTestSuite_TestCloneData;

static class TestDescription_suite_TableTestSuite_TestCloneHelper : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestCloneHelper() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 439, "TestCloneHelper" ) {}
 void runTest() { suite_TableTestSuite.TestCloneHelper(); }
} testDescription_suite_TableTestSuite_TestCloneHelper;

static class TestDescription_suite_TableTestSuite_TestNested : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TableTestSuite_TestNested() : CxxTest::RealTestDescription( Tests_TableTestSuite, suiteDescription_TableTestSuite, 463, "TestNested" ) {}
 void runTest() { suite_TableTestSuite.TestNested(); }
} testDescription_suite_TableTestSuite_TestNested;

