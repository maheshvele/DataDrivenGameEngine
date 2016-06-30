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

bool suite_TetrominoSpawnTestSuite_init = false;
#include "TetrominoSpawnerTest.h"

static TetrominoSpawnTestSuite suite_TetrominoSpawnTestSuite;

static CxxTest::List Tests_TetrominoSpawnTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TetrominoSpawnTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/TetrominoSpawnerTest.h", 19, "TetrominoSpawnTestSuite", suite_TetrominoSpawnTestSuite, Tests_TetrominoSpawnTestSuite );

static class TestDescription_suite_TetrominoSpawnTestSuite_TestWithoutParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TetrominoSpawnTestSuite_TestWithoutParse() : CxxTest::RealTestDescription( Tests_TetrominoSpawnTestSuite, suiteDescription_TetrominoSpawnTestSuite, 46, "TestWithoutParse" ) {}
 void runTest() { suite_TetrominoSpawnTestSuite.TestWithoutParse(); }
} testDescription_suite_TetrominoSpawnTestSuite_TestWithoutParse;

static class TestDescription_suite_TetrominoSpawnTestSuite_TestParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TetrominoSpawnTestSuite_TestParse() : CxxTest::RealTestDescription( Tests_TetrominoSpawnTestSuite, suiteDescription_TetrominoSpawnTestSuite, 150, "TestParse" ) {}
 void runTest() { suite_TetrominoSpawnTestSuite.TestParse(); }
} testDescription_suite_TetrominoSpawnTestSuite_TestParse;

