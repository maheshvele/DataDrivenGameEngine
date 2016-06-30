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

bool suite_TetrominoEntityTest_init = false;
#include "TetrominoEntityTest.h"

static TetrominoEntityTest suite_TetrominoEntityTest;

static CxxTest::List Tests_TetrominoEntityTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TetrominoEntityTest( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/TetrominoEntityTest.h", 19, "TetrominoEntityTest", suite_TetrominoEntityTest, Tests_TetrominoEntityTest );

static class TestDescription_suite_TetrominoEntityTest_TestParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TetrominoEntityTest_TestParse() : CxxTest::RealTestDescription( Tests_TetrominoEntityTest, suiteDescription_TetrominoEntityTest, 47, "TestParse" ) {}
 void runTest() { suite_TetrominoEntityTest.TestParse(); }
} testDescription_suite_TetrominoEntityTest_TestParse;

