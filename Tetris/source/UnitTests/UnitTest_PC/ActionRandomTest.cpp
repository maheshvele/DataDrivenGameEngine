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

bool suite_ActionRandomTestSuite_init = false;
#include "ActionRandomTest.h"

static ActionRandomTestSuite suite_ActionRandomTestSuite;

static CxxTest::List Tests_ActionRandomTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ActionRandomTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/ActionRandomTest.h", 7, "ActionRandomTestSuite", suite_ActionRandomTestSuite, Tests_ActionRandomTestSuite );

static class TestDescription_suite_ActionRandomTestSuite_TestUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionRandomTestSuite_TestUpdate() : CxxTest::RealTestDescription( Tests_ActionRandomTestSuite, suiteDescription_ActionRandomTestSuite, 33, "TestUpdate" ) {}
 void runTest() { suite_ActionRandomTestSuite.TestUpdate(); }
} testDescription_suite_ActionRandomTestSuite_TestUpdate;

