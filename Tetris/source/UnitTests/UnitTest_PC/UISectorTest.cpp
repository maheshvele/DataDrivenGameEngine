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

bool suite_UISectorTest_init = false;
#include "UISectorTest.h"

static UISectorTest suite_UISectorTest;

static CxxTest::List Tests_UISectorTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_UISectorTest( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/UISectorTest.h", 19, "UISectorTest", suite_UISectorTest, Tests_UISectorTest );

static class TestDescription_suite_UISectorTest_TestInstantiate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UISectorTest_TestInstantiate() : CxxTest::RealTestDescription( Tests_UISectorTest, suiteDescription_UISectorTest, 45, "TestInstantiate" ) {}
 void runTest() { suite_UISectorTest.TestInstantiate(); }
} testDescription_suite_UISectorTest_TestInstantiate;

static class TestDescription_suite_UISectorTest_TestRender : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UISectorTest_TestRender() : CxxTest::RealTestDescription( Tests_UISectorTest, suiteDescription_UISectorTest, 56, "TestRender" ) {}
 void runTest() { suite_UISectorTest.TestRender(); }
} testDescription_suite_UISectorTest_TestRender;

static class TestDescription_suite_UISectorTest_TestParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UISectorTest_TestParse() : CxxTest::RealTestDescription( Tests_UISectorTest, suiteDescription_UISectorTest, 77, "TestParse" ) {}
 void runTest() { suite_UISectorTest.TestParse(); }
} testDescription_suite_UISectorTest_TestParse;

