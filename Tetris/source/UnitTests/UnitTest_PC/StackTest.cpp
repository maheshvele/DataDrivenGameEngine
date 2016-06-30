/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_StackTestSuite_init = false;
#include "StackTest.h"

static StackTestSuite suite_StackTestSuite;

static CxxTest::List Tests_StackTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_StackTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/StackTest.h", 7, "StackTestSuite", suite_StackTestSuite, Tests_StackTestSuite );

static class TestDescription_suite_StackTestSuite_TestPushTop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_StackTestSuite_TestPushTop() : CxxTest::RealTestDescription( Tests_StackTestSuite, suiteDescription_StackTestSuite, 25, "TestPushTop" ) {}
 void runTest() { suite_StackTestSuite.TestPushTop(); }
} testDescription_suite_StackTestSuite_TestPushTop;

static class TestDescription_suite_StackTestSuite_TestPop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_StackTestSuite_TestPop() : CxxTest::RealTestDescription( Tests_StackTestSuite, suiteDescription_StackTestSuite, 46, "TestPop" ) {}
 void runTest() { suite_StackTestSuite.TestPop(); }
} testDescription_suite_StackTestSuite_TestPop;

static class TestDescription_suite_StackTestSuite_TestAssign : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_StackTestSuite_TestAssign() : CxxTest::RealTestDescription( Tests_StackTestSuite, suiteDescription_StackTestSuite, 76, "TestAssign" ) {}
 void runTest() { suite_StackTestSuite.TestAssign(); }
} testDescription_suite_StackTestSuite_TestAssign;

