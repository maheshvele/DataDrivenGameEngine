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

bool suite_EventTestSuite_init = false;
#include "EventTests.h"

static EventTestSuite suite_EventTestSuite;

static CxxTest::List Tests_EventTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EventTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/EventTests.h", 8, "EventTestSuite", suite_EventTestSuite, Tests_EventTestSuite );

static class TestDescription_suite_EventTestSuite_TestInstantiation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestInstantiation() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 35, "TestInstantiation" ) {}
 void runTest() { suite_EventTestSuite.TestInstantiation(); }
} testDescription_suite_EventTestSuite_TestInstantiation;

static class TestDescription_suite_EventTestSuite_TestQueueFunctions : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestQueueFunctions() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 47, "TestQueueFunctions" ) {}
 void runTest() { suite_EventTestSuite.TestQueueFunctions(); }
} testDescription_suite_EventTestSuite_TestQueueFunctions;

static class TestDescription_suite_EventTestSuite_TestTimeFunctions : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestTimeFunctions() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 68, "TestTimeFunctions" ) {}
 void runTest() { suite_EventTestSuite.TestTimeFunctions(); }
} testDescription_suite_EventTestSuite_TestTimeFunctions;

static class TestDescription_suite_EventTestSuite_TestSubscription : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestSubscription() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 94, "TestSubscription" ) {}
 void runTest() { suite_EventTestSuite.TestSubscription(); }
} testDescription_suite_EventTestSuite_TestSubscription;

static class TestDescription_suite_EventTestSuite_TestEventQueue : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestEventQueue() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 143, "TestEventQueue" ) {}
 void runTest() { suite_EventTestSuite.TestEventQueue(); }
} testDescription_suite_EventTestSuite_TestEventQueue;

