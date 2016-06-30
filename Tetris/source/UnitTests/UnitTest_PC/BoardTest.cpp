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

bool suite_BoardTest_init = false;
#include "BoardTest.h"

static BoardTest suite_BoardTest;

static CxxTest::List Tests_BoardTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_BoardTest( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/BoardTest.h", 10, "BoardTest", suite_BoardTest, Tests_BoardTest );

static class TestDescription_suite_BoardTest_TestInstantiate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BoardTest_TestInstantiate() : CxxTest::RealTestDescription( Tests_BoardTest, suiteDescription_BoardTest, 38, "TestInstantiate" ) {}
 void runTest() { suite_BoardTest.TestInstantiate(); }
} testDescription_suite_BoardTest_TestInstantiate;

