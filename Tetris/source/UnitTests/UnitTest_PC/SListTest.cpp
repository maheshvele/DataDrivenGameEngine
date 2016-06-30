/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ParenPrinter.h>

int main( int argc, char *argv[] ) {
 int status;

#if defined(DEBUG) || defined(_DEBUG)
_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    CxxTest::ParenPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ParenPrinter >( tmp, argc, argv );
    return status;
}
bool suite_MyTestSuite_init = false;
#include "SListTest.h"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/SListTest.h", 7, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_suite_MyTestSuite_TestEmptyException : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestEmptyException() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 49, "TestEmptyException" ) {}
 void runTest() { suite_MyTestSuite.TestEmptyException(); }
} testDescription_suite_MyTestSuite_TestEmptyException;

static class TestDescription_suite_MyTestSuite_TestPushFront : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestPushFront() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 64, "TestPushFront" ) {}
 void runTest() { suite_MyTestSuite.TestPushFront(); }
} testDescription_suite_MyTestSuite_TestPushFront;

static class TestDescription_suite_MyTestSuite_TestPopFront : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestPopFront() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 81, "TestPopFront" ) {}
 void runTest() { suite_MyTestSuite.TestPopFront(); }
} testDescription_suite_MyTestSuite_TestPopFront;

static class TestDescription_suite_MyTestSuite_TestPushBack : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestPushBack() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 100, "TestPushBack" ) {}
 void runTest() { suite_MyTestSuite.TestPushBack(); }
} testDescription_suite_MyTestSuite_TestPushBack;

static class TestDescription_suite_MyTestSuite_TestCopy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestCopy() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 123, "TestCopy" ) {}
 void runTest() { suite_MyTestSuite.TestCopy(); }
} testDescription_suite_MyTestSuite_TestCopy;

static class TestDescription_suite_MyTestSuite_TestOrder : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestOrder() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 176, "TestOrder" ) {}
 void runTest() { suite_MyTestSuite.TestOrder(); }
} testDescription_suite_MyTestSuite_TestOrder;

static class TestDescription_suite_MyTestSuite_TestIteratorEquality : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestIteratorEquality() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 252, "TestIteratorEquality" ) {}
 void runTest() { suite_MyTestSuite.TestIteratorEquality(); }
} testDescription_suite_MyTestSuite_TestIteratorEquality;

static class TestDescription_suite_MyTestSuite_TestIteratorIncrement : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestIteratorIncrement() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 303, "TestIteratorIncrement" ) {}
 void runTest() { suite_MyTestSuite.TestIteratorIncrement(); }
} testDescription_suite_MyTestSuite_TestIteratorIncrement;

static class TestDescription_suite_MyTestSuite_TestIteratorDereference : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestIteratorDereference() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 358, "TestIteratorDereference" ) {}
 void runTest() { suite_MyTestSuite.TestIteratorDereference(); }
} testDescription_suite_MyTestSuite_TestIteratorDereference;

static class TestDescription_suite_MyTestSuite_TestInsertAfter : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestInsertAfter() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 379, "TestInsertAfter" ) {}
 void runTest() { suite_MyTestSuite.TestInsertAfter(); }
} testDescription_suite_MyTestSuite_TestInsertAfter;

static class TestDescription_suite_MyTestSuite_TestFind : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestFind() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 431, "TestFind" ) {}
 void runTest() { suite_MyTestSuite.TestFind(); }
} testDescription_suite_MyTestSuite_TestFind;

static class TestDescription_suite_MyTestSuite_TestRemove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_TestRemove() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 475, "TestRemove" ) {}
 void runTest() { suite_MyTestSuite.TestRemove(); }
} testDescription_suite_MyTestSuite_TestRemove;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
