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

bool suite_ActionListTestSuite_init = false;
#include "ActionListTest.h"

static ActionListTestSuite suite_ActionListTestSuite;

static CxxTest::List Tests_ActionListTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ActionListTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/ActionListTest.h", 9, "ActionListTestSuite", suite_ActionListTestSuite, Tests_ActionListTestSuite );

static class TestDescription_suite_ActionListTestSuite_TestName : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionListTestSuite_TestName() : CxxTest::RealTestDescription( Tests_ActionListTestSuite, suiteDescription_ActionListTestSuite, 36, "TestName" ) {}
 void runTest() { suite_ActionListTestSuite.TestName(); }
} testDescription_suite_ActionListTestSuite_TestName;

static class TestDescription_suite_ActionListTestSuite_TestGetActions : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionListTestSuite_TestGetActions() : CxxTest::RealTestDescription( Tests_ActionListTestSuite, suiteDescription_ActionListTestSuite, 43, "TestGetActions" ) {}
 void runTest() { suite_ActionListTestSuite.TestGetActions(); }
} testDescription_suite_ActionListTestSuite_TestGetActions;

static class TestDescription_suite_ActionListTestSuite_TestUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionListTestSuite_TestUpdate() : CxxTest::RealTestDescription( Tests_ActionListTestSuite, suiteDescription_ActionListTestSuite, 50, "TestUpdate" ) {}
 void runTest() { suite_ActionListTestSuite.TestUpdate(); }
} testDescription_suite_ActionListTestSuite_TestUpdate;

static class TestDescription_suite_ActionListTestSuite_TestActionInEntity : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionListTestSuite_TestActionInEntity() : CxxTest::RealTestDescription( Tests_ActionListTestSuite, suiteDescription_ActionListTestSuite, 58, "TestActionInEntity" ) {}
 void runTest() { suite_ActionListTestSuite.TestActionInEntity(); }
} testDescription_suite_ActionListTestSuite_TestActionInEntity;

static class TestDescription_suite_ActionListTestSuite_TestActionFactory : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionListTestSuite_TestActionFactory() : CxxTest::RealTestDescription( Tests_ActionListTestSuite, suiteDescription_ActionListTestSuite, 69, "TestActionFactory" ) {}
 void runTest() { suite_ActionListTestSuite.TestActionFactory(); }
} testDescription_suite_ActionListTestSuite_TestActionFactory;

static class TestDescription_suite_ActionListTestSuite_TestEntityCreateAction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionListTestSuite_TestEntityCreateAction() : CxxTest::RealTestDescription( Tests_ActionListTestSuite, suiteDescription_ActionListTestSuite, 83, "TestEntityCreateAction" ) {}
 void runTest() { suite_ActionListTestSuite.TestEntityCreateAction(); }
} testDescription_suite_ActionListTestSuite_TestEntityCreateAction;

