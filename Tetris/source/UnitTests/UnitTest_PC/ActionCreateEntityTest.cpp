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

bool suite_ActionCreateEntityTest_init = false;
#include "ActionCreateEntityTest.h"

static ActionCreateEntityTest suite_ActionCreateEntityTest;

static CxxTest::List Tests_ActionCreateEntityTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ActionCreateEntityTest( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/ActionCreateEntityTest.h", 10, "ActionCreateEntityTest", suite_ActionCreateEntityTest, Tests_ActionCreateEntityTest );

static class TestDescription_suite_ActionCreateEntityTest_TestGetSet : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionCreateEntityTest_TestGetSet() : CxxTest::RealTestDescription( Tests_ActionCreateEntityTest, suiteDescription_ActionCreateEntityTest, 37, "TestGetSet" ) {}
 void runTest() { suite_ActionCreateEntityTest.TestGetSet(); }
} testDescription_suite_ActionCreateEntityTest_TestGetSet;

static class TestDescription_suite_ActionCreateEntityTest_TestUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionCreateEntityTest_TestUpdate() : CxxTest::RealTestDescription( Tests_ActionCreateEntityTest, suiteDescription_ActionCreateEntityTest, 52, "TestUpdate" ) {}
 void runTest() { suite_ActionCreateEntityTest.TestUpdate(); }
} testDescription_suite_ActionCreateEntityTest_TestUpdate;

static class TestDescription_suite_ActionCreateEntityTest_TestFactory : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionCreateEntityTest_TestFactory() : CxxTest::RealTestDescription( Tests_ActionCreateEntityTest, suiteDescription_ActionCreateEntityTest, 76, "TestFactory" ) {}
 void runTest() { suite_ActionCreateEntityTest.TestFactory(); }
} testDescription_suite_ActionCreateEntityTest_TestFactory;

static class TestDescription_suite_ActionCreateEntityTest_TestParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionCreateEntityTest_TestParse() : CxxTest::RealTestDescription( Tests_ActionCreateEntityTest, suiteDescription_ActionCreateEntityTest, 97, "TestParse" ) {}
 void runTest() { suite_ActionCreateEntityTest.TestParse(); }
} testDescription_suite_ActionCreateEntityTest_TestParse;

