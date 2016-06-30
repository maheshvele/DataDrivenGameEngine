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

bool suite_FooTestSuite_init = false;
#include "FooTest.h"

static FooTestSuite suite_FooTestSuite;

static CxxTest::List Tests_FooTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FooTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/FooTest.h", 6, "FooTestSuite", suite_FooTestSuite, Tests_FooTestSuite );

static class TestDescription_suite_FooTestSuite_TestFooInstantiation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FooTestSuite_TestFooInstantiation() : CxxTest::RealTestDescription( Tests_FooTestSuite, suiteDescription_FooTestSuite, 9, "TestFooInstantiation" ) {}
 void runTest() { suite_FooTestSuite.TestFooInstantiation(); }
} testDescription_suite_FooTestSuite_TestFooInstantiation;

