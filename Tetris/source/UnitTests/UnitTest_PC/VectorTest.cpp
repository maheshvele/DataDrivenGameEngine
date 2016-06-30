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

bool suite_VectorTestSuite_init = false;
#include "VectorTest.h"

static VectorTestSuite suite_VectorTestSuite;

static CxxTest::List Tests_VectorTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_VectorTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/VectorTest.h", 7, "VectorTestSuite", suite_VectorTestSuite, Tests_VectorTestSuite );

static class TestDescription_suite_VectorTestSuite_TestFrontAndBack : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestFrontAndBack() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 29, "TestFrontAndBack" ) {}
 void runTest() { suite_VectorTestSuite.TestFrontAndBack(); }
} testDescription_suite_VectorTestSuite_TestFrontAndBack;

static class TestDescription_suite_VectorTestSuite_TestPush : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestPush() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 55, "TestPush" ) {}
 void runTest() { suite_VectorTestSuite.TestPush(); }
} testDescription_suite_VectorTestSuite_TestPush;

static class TestDescription_suite_VectorTestSuite_TestPop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestPop() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 100, "TestPop" ) {}
 void runTest() { suite_VectorTestSuite.TestPop(); }
} testDescription_suite_VectorTestSuite_TestPop;

static class TestDescription_suite_VectorTestSuite_TestOperatorBrackets : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestOperatorBrackets() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 134, "TestOperatorBrackets" ) {}
 void runTest() { suite_VectorTestSuite.TestOperatorBrackets(); }
} testDescription_suite_VectorTestSuite_TestOperatorBrackets;

static class TestDescription_suite_VectorTestSuite_TestAt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestAt() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 184, "TestAt" ) {}
 void runTest() { suite_VectorTestSuite.TestAt(); }
} testDescription_suite_VectorTestSuite_TestAt;

static class TestDescription_suite_VectorTestSuite_TestCopy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestCopy() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 223, "TestCopy" ) {}
 void runTest() { suite_VectorTestSuite.TestCopy(); }
} testDescription_suite_VectorTestSuite_TestCopy;

static class TestDescription_suite_VectorTestSuite_TestIteratorAssign : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorAssign() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 279, "TestIteratorAssign" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorAssign(); }
} testDescription_suite_VectorTestSuite_TestIteratorAssign;

static class TestDescription_suite_VectorTestSuite_TestIteratorEquality : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorEquality() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 319, "TestIteratorEquality" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorEquality(); }
} testDescription_suite_VectorTestSuite_TestIteratorEquality;

static class TestDescription_suite_VectorTestSuite_TestIteratorDereference : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorDereference() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 340, "TestIteratorDereference" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorDereference(); }
} testDescription_suite_VectorTestSuite_TestIteratorDereference;

static class TestDescription_suite_VectorTestSuite_TestIteratorIncrement : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorIncrement() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 366, "TestIteratorIncrement" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorIncrement(); }
} testDescription_suite_VectorTestSuite_TestIteratorIncrement;

static class TestDescription_suite_VectorTestSuite_TestIteratorBeginAndEnd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorBeginAndEnd() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 410, "TestIteratorBeginAndEnd" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorBeginAndEnd(); }
} testDescription_suite_VectorTestSuite_TestIteratorBeginAndEnd;

static class TestDescription_suite_VectorTestSuite_TestIteratorFind : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorFind() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 442, "TestIteratorFind" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorFind(); }
} testDescription_suite_VectorTestSuite_TestIteratorFind;

static class TestDescription_suite_VectorTestSuite_TestRemove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestRemove() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 486, "TestRemove" ) {}
 void runTest() { suite_VectorTestSuite.TestRemove(); }
} testDescription_suite_VectorTestSuite_TestRemove;

static class TestDescription_suite_VectorTestSuite_TestRemoveByIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestRemoveByIndex() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 589, "TestRemoveByIndex" ) {}
 void runTest() { suite_VectorTestSuite.TestRemoveByIndex(); }
} testDescription_suite_VectorTestSuite_TestRemoveByIndex;

